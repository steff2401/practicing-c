#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char *key;
    int value;
} Pair;

typedef struct {
    int capacity, currSize;
    Pair **pairs;
} HashMap;

HashMap* createEmptyMap(int capacity);
int hash(char *key, int capacity);
void put(HashMap *map, char *key, int value);
int get(HashMap *map, char *key);
void delete(HashMap *map, char *key);
void destroyHashMap(HashMap *map);

int main(void) {
    HashMap *map = createEmptyMap(3);
    put(map, "A", 1);
    put(map, "B", 2);
    put(map, "C", 3);
    put(map, "C", 4);

    printf("%d\n", get(map, "A"));
    printf("%d\n", get(map, "B"));
    printf("%d\n", get(map, "C")); // should print 4
    // printf("%d\n", get(map, "D")); // should say key not in map

    delete(map, "C");
    printf("%d\n", get(map, "C")); // should say key not in map

    destroyHashMap(map);
    return 0;
}

HashMap* createEmptyMap(int capacity) {
    HashMap *map = malloc(sizeof(HashMap));
    if (map == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    map->capacity = capacity;
    map->currSize = 0;
    map->pairs = calloc(capacity, sizeof(Pair*));
    if (map->pairs == NULL) {
        printf("Memory allocation failed.\n");
        destroyHashMap(map);
        exit(EXIT_FAILURE);
    }
    // initialize pairs to NULL
    for (int i = 0; i < capacity; i++) {
        map->pairs[i] = NULL; 
    }
    
    return map;
}

int hash(char *key, int capacity) {
    int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        int ascii = (int) key[i];
        hash = 31*hash + ascii;
    }
    return hash % capacity;
}

void put(HashMap *map, char *key, int value) {
    int index = hash(key, map->capacity);
    // if map is full and you try to put in new key-val pair
    if (map->currSize >= map->capacity && map->pairs[index]->key != key) {
        printf("Map is full.\n");
        destroyHashMap(map);
        exit(EXIT_FAILURE);
    }
    
    // if key-val pair doesn't exist from before
    if (map->pairs[index] == NULL) {
        Pair *pair = malloc(sizeof(Pair));
        if (pair == NULL) {
            printf("Memory allocation failed.\n");
            destroyHashMap(map);
            exit(EXIT_FAILURE);
        }
        pair->key = key;
        pair->value = value;
        map->pairs[index] = pair;
        map->currSize++;

    // if you want to update value in key-val pair
    } else if (map->pairs[index]->key == key) {
        map->pairs[index]->value = value;
    }
    //TODO: handle collision
}

int get(HashMap *map, char *key) {
    int index = hash(key, map->capacity);
    if (map->pairs[index] != NULL && map->pairs[index]->key == key) {
        return map->pairs[index]->value;
    }
    printf("Key \"%s\" not in map.\n", key);
    destroyHashMap(map);
    exit(EXIT_FAILURE);
}

void delete(HashMap *map, char *key) {
    int index = hash(key, map->capacity);
    if (map->pairs[index] != NULL && map->pairs[index]->key == key) {
        free(map->pairs[index]);
        map->pairs[index] = NULL;
        map->currSize--;
    } else { 
        printf("Key \"%s\" not in map.\n", key);
    }
}

void destroyHashMap(HashMap *map) {
    for (int i = 0; i < map->capacity; i++) {
        free(map->pairs[i]);
    }
    free(map->pairs);
    free(map);
}
