#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "HashMap.h"
#include "test_SpellMaster.h"
#define MAX_LENGTH 100

int validSpell(HashMap* chosenSpells, char spell[]) {
    return containsKey(chosenSpells, spell);
}

int matchingCharacters(char* spell1, char* spell2) {
    if (spell1 == NULL || spell2 == NULL) {
        return 0;
    }
    int length1 = strlen(spell1);
    char lastCharSpell1 = spell1[length1 - 1];
    char firstCharSpell2 = spell2[0];
    
    return (lastCharSpell1 == firstCharSpell2);
}

int spellExists(HashMap* spellMap, char spell[]) {
    return get(spellMap, spell)!=NULL;
}

int existsAvailableMove(HashMap* spellMap, char opponentSpell[]) {
    if (opponentSpell == NULL || strlen(opponentSpell) == 0) {
        return 0;
    }
    
    // Get the index for the last character of the opponent's spell
    unsigned int index = hash(&opponentSpell[strlen(opponentSpell) - 1]);

    // Check only the spells in the bucket corresponding to the last character
    Entry* entry = spellMap->buckets[index];
    if(entry!=NULL){
        return 1; // Available move found
    }
    return 0; // No available moves found
}

void printSpellTable(HashMap* spellMap) {
    char** keys = getKeys(spellMap);
    int size = getSize(spellMap);

    for (int i = 0; i < size; i++) {
        printf("%-20s", keys[i]);
        if ((i + 1) % 5 == 0) {
            printf("\n");
        }
    }

    if (size % 5 != 0) {
        printf("\n");
    }

    free(keys);
}

int coinFlip() {
    srand(time(NULL));
    return rand() % 2;
}

// A helper function to count how many spells start with a given character
int getStartsWithCount(HashMap* spellMap, char startChar) {
    int count = 0;
    int index = startChar - 'a';
    Entry* entry = spellMap->buckets[index];
    while (entry) {
        count++;
        entry = entry->next;
    }
    return count;
}

// This function assigns scores to spells when they are read from the file
void updateScores(HashMap* spellMap) {
    for (int i = 0; i < spellMap->capacity; i++) {
        Entry* entry = spellMap->buckets[i];
        while (entry) {
            // Subtract the count of spells that start with the last character of this spell
            char lastChar = entry->key[strlen(entry->key) - 1];
            int count = getStartsWithCount(spellMap, lastChar);
            entry->score = 10 - count;
            entry = entry->next;
        }
    }
}
// This function gets the move for the easy bot
char* getEasyMove(HashMap* spellMap, char* lastSpell) {
    char* easyMove = NULL;
    unsigned int index;

    // If it's the bot's first move, choose the spell with the highest score
    if(lastSpell == NULL || lastSpell[0] == '\0') {
        for (int i = 0; i < spellMap->capacity/2; i++) {
            int j = 0;
            Entry* entry = spellMap->buckets[i];
            while (entry && j<2) {
                easyMove = entry->key;
                entry = entry->next;
                j++;
            }
        }
    } else {
        // If it's not the first move, find the best scoring move that matches the last character of the lastSpell
        char lastChar = tolower(lastSpell[strlen(lastSpell) - 1]);
        index = hash(&lastChar);
        int j = 0;
        Entry* entry = spellMap->buckets[index];
        while (entry && j<2) {
            easyMove = entry->key;
            entry = entry->next;
            j++;
        }
    }
    return easyMove;
}

// This function gets the move for the medium bot
char* getMediumMove(HashMap* spellMap, char* lastSpell) {
    int score = 0;
    int maxMediumScore = 0;
    char* mediumMove = NULL;
    unsigned int index;

    // If it's the bot's first move, choose the spell with the highest score
    if(lastSpell == NULL || lastSpell[0] == '\0') {
        for (int i = 0; i < spellMap->capacity; i++) {
            int mediumScore = 0;
            char* tempMove = NULL;
            Entry* scoreEntry = spellMap->buckets[i];
            while (scoreEntry) {
                score += scoreEntry->score;
                scoreEntry = scoreEntry->next;
            }
            Entry* entry = spellMap->buckets[i];
            while(entry && mediumScore <= score/2){
                mediumScore += entry->score;
                tempMove = entry->key;
                entry = entry->next;
            }
            if(mediumScore >= maxMediumScore){
                mediumMove = tempMove;
                maxMediumScore = mediumScore;
            }
        }
    } else {
        // If it's not the first move, find the best scoring move that matches the last character of the lastSpell
        char lastChar = tolower(lastSpell[strlen(lastSpell) - 1]);
        index = hash(&lastChar);
        Entry* scoreEntry = spellMap->buckets[index];
        while (scoreEntry) {
            score += scoreEntry->score;
            scoreEntry = scoreEntry->next;
        }
        Entry* entry = spellMap->buckets[index];
        while(entry && maxMediumScore <= score/2){
            maxMediumScore += entry ->score;
            mediumMove = entry ->key;
            entry = entry->next;
        }
    }
    return mediumMove;
}

// This function gets the best move for the bot
char* getBestMove(HashMap* spellMap, char* lastSpell) {
    int bestScore = -1;
    char* bestMove = NULL;
    unsigned int index;

    // If it's the bot's first move, choose the spell with the highest score
    if(lastSpell == NULL || lastSpell[0] == '\0') {
        for (int i = 0; i < spellMap->capacity; i++) {
            Entry* entry = spellMap->buckets[i];
            while (entry) {
                if (entry->score > bestScore) {
                    bestScore = entry->score;
                    bestMove = entry->key;
                }
                entry = entry->next;
            }
        }
    } else {
        // If it's not the first move, find the best scoring move that matches the last character of the lastSpell
        char lastChar = tolower(lastSpell[strlen(lastSpell) - 1]);
        index = hash(&lastChar);
        Entry* entry = spellMap->buckets[index];
        while (entry) {            
            if(entry->score > bestScore) {
                bestScore = entry->score;
                bestMove = entry->key;
                }
            entry = entry->next;
        }
    }
    return bestMove;
}

int main() {
    srand(time(NULL));
    runTests();
    FILE *spellsFile = fopen("spells.txt", "r");

    if (spellsFile == NULL) {
        perror("Error opening spells.txt");
        return 1;
    }

    HashMap* spellMap = createHashMap(MAX_LENGTH);
    HashMap* castedSpells = createHashMap(MAX_LENGTH);


    int numSpells;
    fscanf(spellsFile, "%d", &numSpells);

    for(int i = 0; i < numSpells; i++){
        char spell[MAX_LENGTH];
        fscanf(spellsFile, "%s", spell);
        put(spellMap, &spell[0], spell,0);
    }

    fclose(spellsFile);
    updateScores(spellMap);
    printSpellTable(spellMap);
    printf("\n\n");
    char user1[100];
    char user2[100];
    int difficulty; 
    printf("Player 1 enter your username :");
    scanf("%s", user1);
    printf("\n");
    printf("Choose difficulty(1: easy, 2: medium, 3: hard): ");
    scanf("%d", &difficulty);
    printf("\n");
    printf("Wizards Start ! \n");

    int count = coinFlip();
    int turn = 0;
    char spell1[MAX_LENGTH];
    char spell2[MAX_LENGTH];
    char* tempSpell;
    while (1){
        if(getSize(spellMap) == 0){
            if(count%2 == 0){
                printf("bot wins (The list is empty)");
                break;
            }
            else{
                printf("%s wins (The list is empty)",user1);
                break;
            }
            break;
        }
        if(turn%2 == 0 && turn > 0){
            printSpellTable(spellMap);
        }
        if(count%2 == 0){
            printf("\n- %s chooses: ", user1);
            scanf("%99s",spell1);
            
            if(matchingCharacters(spell2,spell1) == 1 && existsAvailableMove(spellMap, spell1) == 0){
                printf("%s wins (no more spells in the list satisfying the conditions)",user1);
                break;
            }

            if(validSpell(castedSpells, spell1) == 1){
                printf("bot wins (%s repeated a previously casted spell)",user1);
                break;
            }

            if(spellExists(spellMap, spell1) == 0){
                printf("\nbot wins (%s spell is not in the list)",user1);
                break;
            }

            if(count>0 && matchingCharacters(spell2,spell1) == 0){
                printf("bot wins (%s casts a spell with unmatched characters)",user1);
                break;
            }

            put(castedSpells,&spell1[0],spell1,0);
            removeKey(spellMap, spell1);
        }
        else{
            switch (difficulty) {
                case 1:
                    if(turn == 0){
                        tempSpell = getEasyMove(spellMap,NULL);
                        }
                    else{ 
                        tempSpell = getEasyMove(spellMap, spell1);
                    }
                    break;
                case 2:
                    if(turn == 0){
                        tempSpell = getMediumMove(spellMap,NULL);
                        }
                    else{ 
                        tempSpell = getMediumMove(spellMap, spell1);
                    }
                    break;
                case 3:
                    if(turn == 0){
                        tempSpell = getBestMove(spellMap,NULL);
                        }
                    else{ 
                        tempSpell = getBestMove(spellMap, spell1);
                    }
                    break;
            }
            
            if (tempSpell != NULL) {
                strncpy(spell2, tempSpell, MAX_LENGTH);
            }
            printf("\n- bot chooses: %s\n", spell2);
            
            if(existsAvailableMove(spellMap,spell2) == 0){
                printf("bot wins (no more spells in the list satisfying the conditions)");
                break;
            }

            put(castedSpells,&spell2[0],spell2,0);
            removeKey(spellMap, spell2);
        }
        count++;
        turn++;
        updateScores(spellMap);
    }

    destroyHashMap(spellMap);
    destroyHashMap(castedSpells);
    return 0;

}