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

void put(HashMap *map, char *key, int value) {
    size_t index = hash(key, map->maxSize);
    // if map is full and you try to put in new key-val pair
    if (map->currSize >= map->maxSize && strcmp(map->pairs[index]->key, key) != 0) {
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
    } else if (strcmp(map->pairs[index]->key, key) == 0) {
        map->pairs[index]->value = value;
    }
    //TODO: handle collision
}

int get(HashMap *map, char *key) {
    size_t index = hash(key, map->maxSize);
    if (map->pairs[index] != NULL && strcmp(map->pairs[index]->key, key) == 0) {
        return map->pairs[index]->value;
    }
    printf("Key \"%s\" not in map.\n", key);
    destroyHashMap(map);
    exit(EXIT_FAILURE);
}

void delete(HashMap *map, char *key) {
    size_t index = hash(key, map->maxSize);
    if (map->pairs[index] != NULL && strcmp(map->pairs[index]->key, key) == 0) {
        free(map->pairs[index]);
        map->pairs[index] = NULL;
        map->currSize--;
    } else { 
        printf("Key \"%s\" not in map.\n", key);
    }
}

void destroyHashMap(HashMap *map) {
    for (int i = 0; i < map->maxSize; i++) {
        free(map->pairs[i]);
    }
    free(map->pairs);
    free(map);
}
