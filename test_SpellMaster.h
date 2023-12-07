#ifndef TEST_SPELLMASTER_H
#define TEST_SPELLMASTER_H
#include "HashMap.h"
#include "SpellMaster.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

void test_createHashMap();
void test_putAndGet();
void test_removeKey();
void test_validSpell();
void test_matchingCharacters();
void test_spellExists();
void test_existsAvailableMove();
void test_updateScores();
void test_getEasyMove();
void test_getMediumMove();
void test_getBestMove();

void runTests() {
    printf("Running tests...\n");
    test_createHashMap();
    test_putAndGet();
    test_removeKey();
    test_validSpell();
    test_matchingCharacters();
    test_spellExists();
    test_existsAvailableMove();
    test_updateScores();
    test_getEasyMove();
    test_getMediumMove();
    test_getBestMove();
    printf("All tests passed!\n");
}


void test_createHashMap() {
    HashMap* map = createHashMap();
    assert(map != NULL);
    assert(map->capacity == MAX_CAPACITY);
    destroyHashMap(map);
}

void test_putAndGet() {
    HashMap* map = createHashMap();
    char* key = "test";
    char* value = "value";
    put(map, key, value, 10);
    assert(strcmp((char *)get(map, key), value) == 0);
    destroyHashMap(map);
}

void test_getKeys() {
    HashMap* map = createHashMap();

    char* key1 = "alpha";
    char* value1 = "first";
    put(map, key1, value1, 0);

    char* key2 = "beta";
    char* value2 = "second";
    put(map, key2, value2, 0);

    char** keys = getKeys(map);
    int size = getSize(map);
    assert(size == 2);

    int foundKey1 = 0, foundKey2 = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(keys[i], key1) == 0) {
            foundKey1 = 1;
        }
        if (strcmp(keys[i], key2) == 0) {
            foundKey2 = 1;
        }
    }
    assert(foundKey1 == 1);
    assert(foundKey2 == 1);

    free(keys);
    destroyHashMap(map);
}


void test_removeKey() {
    HashMap* map = createHashMap();
    char* key = "test";
    put(map, key, "value", 0);
    removeKey(map, key);
    assert(get(map, key) == NULL);
    destroyHashMap(map);
}

void test_validSpell() {
    HashMap* castedSpells = createHashMap();
    char* key = strdup("test");
    put(castedSpells, key, key, 0);
    assert(validSpell(castedSpells, key) == 1);
    assert(validSpell(castedSpells, "nonexistent") == 0);
    destroyHashMap(castedSpells);
}

void test_matchingCharacters() {
    assert(matchingCharacters("hello", "orange") == 1);
    assert(matchingCharacters("magic", "cat") == 1);
    assert(matchingCharacters(NULL, "test") == 0);
    assert(matchingCharacters("test", NULL) == 0);
}

void test_spellExists() {
    HashMap* spellMap = createHashMap();
    put(spellMap, "test", "value", 0);
    assert(spellExists(spellMap, "test") == 1);
    assert(spellExists(spellMap, "nonexistent") == 0);
    destroyHashMap(spellMap);
}

void test_existsAvailableMove() {
    HashMap* spellMap = createHashMap();
    put(spellMap, "alpha", NULL, 0);
    put(spellMap, "echo", NULL, 0); 
    assert(existsAvailableMove(spellMap, "delta") == 1); 
    assert(existsAvailableMove(spellMap, "lemon") == 0);
    destroyHashMap(spellMap);
}


void test_updateScores() {
    HashMap* spellMap = createHashMap();
    put(spellMap, "fire", "fire", 0);
    put(spellMap, "ice", "ice", 0); 
    put(spellMap, "wind", "wind", 0);
    put(spellMap, "earth", "earth", 0);
    put(spellMap, "water", "water", 0); 
    updateScores(spellMap);
    char **keys = getKeys(spellMap);
    int size = getSize(spellMap);
    assert(size == 5);
    for (int i = 0; i < size; i++) {
        Entry *entry = spellMap->buckets[i];
        while (entry) {
            assert(entry->score != 0);
            entry = entry->next;
        }
    }
    destroyHashMap(spellMap);
}

void test_getEasyMove() {
    HashMap* spellMap = createHashMap();
    put(spellMap, "alpha", "value", 0);
    put(spellMap, "beta", "value", 0);

    char* move = getEasyMove(spellMap, NULL);
    assert(strcmp(move, "alpha") == 0 || strcmp(move, "beta") == 0);

    destroyHashMap(spellMap);
}

void test_getMediumMove() {
    HashMap* spellMap = createHashMap();
    put(spellMap, "cat", "value", 5);
    put(spellMap, "dog", "value", 6);

    char* move = getMediumMove(spellMap, NULL);
    assert(strcmp(move, "cat") == 0 || strcmp(move, "dog") == 0);

    destroyHashMap(spellMap);
}

void test_getBestMove() {
    HashMap* spellMap = createHashMap();
    put(spellMap, "echo", "value", 2);
    put(spellMap, "foxtrot", "value", 3);

    char* move = getBestMove(spellMap, NULL);
    assert(strcmp(move, "foxtrot") == 0);

    destroyHashMap(spellMap);
}
#endif