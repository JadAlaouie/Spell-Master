Game Report: SpellMaster - ByteForce

Introduction:
SpellMaster is a spell-casting game where players compete against a bot across varying difficulty levels. The core of the game is to cast spells in a strategic manner, with each spell having unique characteristics and scores. The game's logic is implemented in C, featuring a custom HashMap for efficient data management and various strategies for the bot corresponding to different difficulty levels.

1. Classes and Data Structures
HashMap Class

File: HashMap.h
Purpose: To store and manage spell data and scores.
Key Functions:
createHashMap: Initializes a new HashMap. Crucial for starting the game with a clean slate.
put: Inserts a spell and its associated score into the HashMap. Used for initializing the game state with available spells.
get: Retrieves a spell's data from the HashMap. Essential for accessing spell information during gameplay.
removeKey: Removes a spell from the HashMap, used when a spell is cast and is no longer available.
getSize: Returns the number of spells currently in the HashMap. Useful for tracking game progress and available spells.
hash: A simple hashing function mapping a key (spell) to a bucket based on its first character. This function is vital for the efficient organization and retrieval of spells.
getKeys: Provides a list of all spell keys in the HashMap. Useful for displaying available spells.

SpellMaster Class

File: SpellMaster.c
Purpose: Implements the game's logic, including spell validation, bot moves, and scoring.
Key Functions:
validSpell: Checks if a spell has already been cast, preventing repeat moves.
matchingCharacters: Ensures the last character of the previously cast spell matches the first character of the current spell, enforcing game rules.
spellExists: Verifies if a spell is available in the spellMap.
existsAvailableMove: Determines if there are any valid spells remaining that can be cast.
printSpellTable: Displays the current available spells in the game.
coinFlip: Randomly decides who starts the game – the player or the bot.
getEasyMove, getMediumMove, getBestMove: Determines the bot's move based on the chosen difficulty level.
2. Function specifications
1- validSpell

Precondition:
chosenSpells must be a valid pointer to an initialized HashMap.
spell must be a valid string.

Postcondition:
Returns 1 (true) if spell exists in chosenSpells.
Returns 0 (false) if spell does not exist in chosenSpells.

2- matchingCharacters

Precondition:
spell1 and spell2 must be valid string pointers or NULL.

Postcondition:
Returns 1 (true) if the last character of spell1 matches the first character of spell2.
Returns 0 (false) if spell1 or spell2 is NULL, empty, or if their relevant characters do not match.

3- spellExists

Precondition:

spellMap must be a valid pointer to an initialized HashMap.
spell must be a valid string.

Postcondition:

Returns 1 (true) if spell exists in spellMap.
Returns 0 (false) if spell does not exist in spellMap.
4- existsAvailableMove

Precondition:

spellMap must be a valid pointer to an initialized HashMap.
opponentSpell must be a valid string pointer or NULL.

Postcondition:

Returns 1 (true) if there is at least one spell in spellMap that can be cast following opponentSpell.
Returns 0 (false) if opponentSpell is NULL, empty, or if no valid spell can follow opponentSpell.

5- printSpellTable
Precondition:
SpellMap must be a valid pointer to an initialized HashMap.

Postcondition: 
Prints the table of spells stored in spellMap.

6- coinFlip
Precondition: 
srand should have been called to initialize the random number generator.

Postcondition: 
Returns a pseudo-random integer 0 or 1.

7- getStartsWithCount

Precondition:

spellMap must be a valid pointer to an initialized HashMap.
startChar must be a valid character.

Postcondition: 
Returns the count of spells in spellMap that start with startChar.

8- updateScores

Precondition: 
spellMap must be a valid pointer to an initialized HashMap.

Postcondition: 
Updates the scores of all spells in spellMap based on the number of spells that start with their last character.

9- getEasyMove, getMediumMove, getBestMove

Precondition:

spellMap must be a valid pointer to an initialized HashMap.
lastSpell must be a valid string pointer or NULL.

Postcondition:

getEasyMove: Returns a spell from the first half of the hashmap buckets or the first few spells in the bucket matching the last character of lastSpell.
getMediumMove: Returns a spell approximately in the middle of the score range from either the whole map or the bucket matching the last character of lastSpell.
getBestMove: Returns the spell with the highest score from either the whole map or the bucket matching the last character of lastSpell.

3. Hashmap Implementation and Hashing Function
The HashMap utilizes a simple yet effective hashing function that maps a spell's key to a specific bucket in the array based on the ASCII value of its first character. This implementation allows for efficient storage and retrieval of spells, which is crucial for the game's performance, especially as the number of spells increases.

4. Bot Strategy and Scoring System
The spells in the hashmap have a score associated with it, this score is calculated based on the number of spells that a certain spell can lead to, i.e the number of spells in the bucket of the hashmap corresponding to the last character in that spell. This is the heuristic strategy used for the bot. Each bot chooses its spell based on a strategy:
Easy bot: chooses a spell from the first half of the hashmap buckets or the first few spells in the bucket matching the last character of lastSpell.
Medium bot: it chooses a spell approximately in the middle of the score range from either the whole map or the bucket matching the last character of lastSpell.
Hard bot: always chooses the spell that has the highest score from the bucket.
5. Testing
Test Cases and Strategy
The test_SpellMaster.h file contains several unit tests designed to validate the functionality of each component in the game. Key test cases include:
Creating and destroying a HashMap.
Inserting, retrieving, and removing spells.
Validating spell existence and matching logic.
Testing the bot strategies for each difficulty level.
These tests ensure the game functions as expected, providing a robust and error-free gaming experience.

