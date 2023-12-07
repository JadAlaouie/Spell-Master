#ifndef SPELLMASTER_H
#define SPELLMASTER_H
#include "HashMap.h"

// Function declarations
int validSpell(HashMap* chosenSpells, char spell[]);
int matchingCharacters(char* spell1, char* spell2);
int spellExists(HashMap* spellMap, char spell[]);
int existsAvailableMove(HashMap* spellMap, char opponentSpell[]);
void printSpellTable(HashMap* spellMap);
int coinFlip();
int getStartsWithCount(HashMap* spellMap, char startChar);
void updateScores(HashMap* spellMap);
char* getEasyMove(HashMap* spellMap, char* lastSpell);
char* getMediumMove(HashMap* spellMap, char* lastSpell);
char* getBestMove(HashMap* spellMap, char* lastSpell);

#endif
