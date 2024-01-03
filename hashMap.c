#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Pair {
    char *key;
    int value;
    struct Pair *next;
} Pair;

typedef struct {
    size_t maxSize, currSize;
    Pair **pairs;
} HashMap;

HashMap* createEmptyMap(size_t maxSize);
size_t hash(HashMap *map, char *key);
int put(HashMap *map, char *key, int value);
int get(HashMap *map, char *key, int *value);
int delete(HashMap *map, char *key);
void destroyHashMap(HashMap *map);
void printHashMap(HashMap* map);

int main(void) {
    // Create a hash map with a limited size to cause collisions
    HashMap* hashMap = createEmptyMap(5);

    printf("Hash Map Test:\n\n");

    // Test 1: Add multiple elements to the hash map
    printf("Test 1: Put elements in the hash map\n");
    for (int i = 0; i < 10; ++i) {
        char key[2];
        sprintf(key, "%c", 'A' + i); // Create keys "A", "B", "C", etc.
        put(hashMap, key, i + 1);    // Values will be 1, 2, 3, etc.
    }
    printHashMap(hashMap);
    printf("\n");    

    // Test 2: Delete elements and ensure they're removed properly
    printf("Test 2: Delete some elements and ensure proper removal\n");
    delete(hashMap, "C");
    delete(hashMap, "H");
    int success, value;
    success = get(hashMap, "C", &value) == -1 && get(hashMap, "H", &value) == -1;
    printHashMap(hashMap);
    printf("%s\n\n", success ? "Test 2 passed" : "Test 2 failed");
    
    // Free memory
    destroyHashMap(hashMap);
    printf("All tests completed\n");

    return 0;
}

/**
 * Summary: initialize an emtpy hash map
 * Parameters: maxSize - how many buckets the map will have
 * Return: pointer to initialized hash map
*/
HashMap* createEmptyMap(size_t maxSize) {
    HashMap *map = malloc(sizeof(HashMap));
    if (map == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    map->maxSize = maxSize;
    map->currSize = 0;
    map->pairs = calloc(maxSize, sizeof(Pair*));
    if (map->pairs == NULL) {
        printf("Memory allocation failed.\n");
        destroyHashMap(map);
        exit(EXIT_FAILURE);
    }

    return map;
}

/**
 * Summary: Hash a given string to valid index
 * Parameters: map - pointer to hash map
 *             key - string to be hashed 
 * Return: The hashed value/a valid index
*/
size_t hash(HashMap *map, char* key) {
    size_t hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        int ascii = (int) key[i];
        hash = 31*hash + ascii;
    }
    return hash % map->maxSize;
}

/**
 * Summary: Put a key-value pair into the hash map or update existing value
 * Parameters: map - pointer to hash map
 *             key - key in the key-value pair
 *             value - value in the key-value pair
 * Return: 0 if sucessful, else -1
*/
int put(HashMap *map, char *key, int value) {
    size_t index = hash(map, key);

    // If bucket is empty
    if (map->pairs[index] == NULL) {
        Pair *newPair = malloc(sizeof(Pair));
        newPair->key = strdup(key);
        if (newPair->key == NULL) {
            free(newPair);
            printf("Memory allocation failed.");
            exit(EXIT_FAILURE);
        }
        newPair->value = value;
        newPair->next = NULL;
        map->pairs[index] = newPair;
        map->currSize++;
        return 0;
    }
    
    // Check if the key already exists in the bucket
    Pair *pair = map->pairs[index];
    while(pair != NULL){
        // If the key is already present, change the value
        if(strcmp(pair->key, key) == 0) {
            pair->value = value;
            return 0;
        }
        if (pair->next == NULL) {
            break;
        }
        pair = pair->next;
    }

    // If the key is not already present, we have collision
    Pair *newPair = malloc(sizeof(Pair));
    newPair->key = strdup(key);
    if (newPair->key == NULL) {
        free(newPair);
        printf("Memory allocation failed.");
        exit(EXIT_FAILURE);
    }
    newPair->value = value;
    newPair->next = NULL;
    pair->next = newPair;
    map->currSize++;
    return 0;
}

/**
 * Summary: Retrieve value for the given key
 * Parameters: map - pointer to hash map
 *             key - key in key-value pair
 *             value - adress to store the value from the retrieved key-value pair 
 * Return: 0 if sucessful, else -1
*/
int get(HashMap *map, char *key, int *value) {
    size_t index = hash(map, key);

    Pair *pair = map->pairs[index];
    while (pair != NULL) {
        if (strcmp(pair->key, key) == 0) {
            *value = pair->value;
            return 0;
        }
        pair = pair->next;
    }

    printf("Key \"%s\" not in map.\n", key);
    return -1;
}

/**
 * Summary: Remove key-value pair from hash map
 * Parameters: map - pointer to hash map
 *             key - key in key-value pair
 * Return: 0 if sucessful, else -1
*/
int delete(HashMap *map, char *key) {
    size_t index = hash(map, key);
    Pair *pair = map->pairs[index];
    Pair *prev = NULL;

    // Loop through bucket to find pair
    while (pair != NULL) {
        if (strcmp(pair->key, key) == 0) {
            // If pair to be deleted is first in bucket
            if (prev == NULL) {
                map->pairs[index] = pair->next;
            } else {
                // Pair to be deleted is not the first, link previous to next
                prev->next = pair->next;
            }
            
            // Free memory
            free(pair->key);
            free(pair);
            map->currSize--;
            return 0;
        }
        prev = pair;
        pair = pair->next;
    }

    // If pair not found
    printf("Key \"%s\" not in map.\n", key);
    return -1;
}


/**
 * Summary: Free allocated memory associated with the hash map
 * Parameters: map - pointer to hash map
 * Return: void
*/
void destroyHashMap(HashMap *map) {
    for (int i = 0; i < map->maxSize; i++) {
        Pair *pair = map->pairs[i];
        while (pair != NULL) {
            Pair *tmp = pair;
            pair = pair->next;
            free(tmp->key);
            free(tmp);
        }
    }
    free(map->pairs);
    free(map);
}

/**
 * Summary: Prints key-value pairs in map following the bucket structure
 * Parameters: map - pointer to hash map
 * Return: void
*/
void printHashMap(HashMap* map) {

    printf("HashMap Contents:\n");
    for (int i = 0; i < map->maxSize; i++) {
        Pair* currentPair = map->pairs[i];
        printf("Bucket %d: ", i);
        if (currentPair == NULL) {
            printf("Empty\n");
        } else {
            // Iterate through the linked list in the current bucket
            int pairIndex = 0;
            while (currentPair != NULL) {
                printf("(%s, %d)", currentPair->key, currentPair->value);
                currentPair = currentPair->next;
                if(currentPair != NULL) {
                    printf(" -> ");
                }
                pairIndex++;
            }
            printf("\n");
        }
    }
}
