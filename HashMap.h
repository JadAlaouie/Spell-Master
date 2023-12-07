#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAPACITY 26  // One bucket for each letter of the alphabet

typedef struct Entry {
    char* key;
    void* value;
    int score;
    struct Entry* next;
} Entry;

typedef struct HashMap {
    Entry** buckets;
    int capacity;
    int size;
} HashMap;

int getSize(HashMap* map);

HashMap* createHashMap() {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    if (!map) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    map->capacity = MAX_CAPACITY;
    map->buckets = (Entry**)calloc(MAX_CAPACITY, sizeof(Entry*));
    if (!map->buckets) {
        perror("Memory allocation error");
        free(map);
        exit(EXIT_FAILURE);
    }

    return map;
}

unsigned int hash(char* key) {
    if (key == NULL || key[0] == '\0') {
        return 0; 
    }
    return (unsigned int)(key[0] - 'a');
}

void put(HashMap* map, char* key, void* value, int score) {
    unsigned int index = hash(key);

    Entry* newEntry = (Entry*)malloc(sizeof(Entry));
    if (!newEntry) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    newEntry->key = strdup(key);
    if (!newEntry->key) {
        perror("Memory allocation error");
        free(newEntry);
        exit(EXIT_FAILURE);
    }

    newEntry->value = value;
    newEntry->score = score;
    newEntry->next = map->buckets[index];
    map->buckets[index] = newEntry;
    map->size++;
}

void* get(HashMap* map, char* key) {
    unsigned int index = hash(key);

    Entry* entry = map->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }

    return NULL;
}

int containsKey(HashMap* map, char* key) {
    return get(map, key) != NULL;
}

void removeKey(HashMap* map, char* key) {
    unsigned int index = hash(key);

    Entry* prev = NULL;
    Entry* current = map->buckets[index];

    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                map->buckets[index] = current->next;
            }

            free(current->key);
            free(current);
            return;
        }

        prev = current;
        current = current->next;
    }
}

char** getKeys(HashMap* map) {
    char** keys = (char**)malloc(sizeof(char*) * getSize(map));
    int index = 0;

    for (int i = 0; i < map->capacity; i++) {
        Entry* entry = map->buckets[i];
        while (entry) {
            keys[index] = entry->key;
            entry = entry->next;
            index++;
        }
    }
    return keys;
}

int getSize(HashMap* map) {
    int size = 0;
    for (int i = 0; i < map->capacity; i++) {
        Entry* entry = map->buckets[i];
        while (entry) {
            size++;
            entry = entry->next;
        }
    }
    return size;
}

void destroyHashMap(HashMap* map) {
    for (int i = 0; i < map->capacity; i++) {
        Entry* entry = map->buckets[i];
        while (entry) {
            Entry* temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp);
        }
    }
    free(map->buckets);
    free(map);
    map->size = 0;
}

#endif 
