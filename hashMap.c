#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} Pair;

typedef struct {
    size_t maxSize, currSize;
    Pair **pairs;
} HashMap;

HashMap* createEmptyMap(size_t maxSize);
size_t hash(char *key, size_t maxSize);
int put(HashMap *map, char *key, int value);
int get(HashMap *map, char *key, int *value);
int delete(HashMap *map, char *key);
void destroyHashMap(HashMap *map);

int main(void) {
    HashMap *map = createEmptyMap(3);

    if (put(map, "A", 1) == -1 || put(map, "B", 2) == -1 || 
        put(map, "C", 3) == -1 || put(map, "C", 4) == -1) {
            printf("Error in put()-function.\n");
            destroyHashMap(map);
            exit(EXIT_FAILURE);
    }

    int val1, val2, val3;
    if (get(map, "A", &val1) == -1 || get(map, "B", &val2) == -1 || get(map, "C", &val3) == -1) {
        printf("Error in get()-function.\n");
    }

    printf("A:%d, B:%d, C:%d\n", val1, val2, val3);

    destroyHashMap(map);
    return 0;
}

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

size_t hash(char *key, size_t maxSize) {
    size_t hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        int ascii = (int) key[i];
        hash = 31*hash + ascii;
    }
    return hash % maxSize;
}

int put(HashMap *map, char *key, int value) {
    //TODO: handle collision

    size_t index = hash(key, map->maxSize);
    // if map is full and you try to put in new key-val pair
    if (map->currSize >= map->maxSize && strcmp(map->pairs[index]->key, key) != 0) {
        printf("Map is full.\n");
        return -1;
    }
    
    // if key-val pair doesn't exist from before
    if (map->pairs[index] == NULL) {
        Pair *pair = malloc(sizeof(Pair));
        if (pair == NULL) {
            printf("Memory allocation failed.\n");
            destroyHashMap(map);
            exit(EXIT_FAILURE);
        }
        pair->key = strdup(key); // duplicate key to make HashMap owner of it
        if (pair->key == NULL) {
            printf("Memory allocation failed.\n");
            destroyHashMap(map);
            exit(EXIT_FAILURE);
        }
        pair->value = value;
        map->pairs[index] = pair;
        map->currSize++;

    // if you want to update value in key-val pair
    } else if (strcmp(map->pairs[index]->key, key) == 0) {
        map->pairs[index]->value = value;
    }
    return 0;
}

int get(HashMap *map, char *key, int *value) {
    //TODO: handle collision

    size_t index = hash(key, map->maxSize);
    if (map->pairs[index] != NULL && strcmp(map->pairs[index]->key, key) == 0) {
        *value = map->pairs[index]->value;
        return 0;

    } else {
        printf("Key \"%s\" not in map.\n", key);
        return -1;
    }
}

int delete(HashMap *map, char *key) {
    //TODO: handle collision

    size_t index = hash(key, map->maxSize);
    if (map->pairs[index] != NULL && strcmp(map->pairs[index]->key, key) == 0) {
        free(map->pairs[index]->key);
        free(map->pairs[index]);
        map->pairs[index] = NULL;
        map->currSize--;
        return 0;
    } else { 
        printf("Key \"%s\" not in map.\n", key);
        return -1;
    }
}

void destroyHashMap(HashMap *map) {
    for (int i = 0; i < map->maxSize; i++) {
        if (map->pairs[i] != NULL) {
            free(map->pairs[i]->key);
            free(map->pairs[i]); 
        }
    }
    free(map->pairs);
    free(map);
}
