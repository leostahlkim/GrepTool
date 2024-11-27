/*
 *  wordHash.cpp
 *  Name: Leo Kim
 *  Date: 4/9/22
 *
 *  Purpose: Implementation of the wordHash class.
        Handles everything with the hash table,
        including the creation of it, hashing items,
        inserting items, and expanding the hash table.
 */

#include "wordHash.h"

/* Name: Constructor
*  Purpose: Constructs an initial hash table with empty wordSensitives
*  Arguments: none
*  Effects: creates a hash table
*  Returns: none
*/ 
wordHash::wordHash() {
    currentTableSize = INITIAL_TABLE_SIZE;
    numItemsInTable  = 0;
    wordTable = new wordSensitive[currentTableSize];
}

/* Name: Destructor
*  Purpose: Deletes the hash table
*  Arguments: none
*  Effects: Recycles the heap memory of the hash table
*  Returns: none
*/ 
wordHash::~wordHash() {
    delete [] wordTable;
}

/* Name: insert
*  Purpose: Insert a word into the hash table
*  Arguments: a wordSensitive, which contains a word
*  Effects: Hashes the word passed in and adds it to the hash table. If index
*  that the hash returns already has a wordSensitive, then the word is added to
*  the appearances array, meaning that this word is another appearance of a 
*  word that was processed earlier
*  Returns: none
*/ 
void wordHash::insert(wordSensitive word) {
    bool found = false;
    float loadFactor = (float)numItemsInTable / (float)currentTableSize;
    if (loadFactor > 0.7) {
        expand();
    }

    int hashedLoc = hashFunc(word.getWord()) % currentTableSize;

    while (not found) {
        wordSensitive *curr = &wordTable[hashedLoc];
        if (curr->isEmpty() and curr->isInsEmpty()) {
            *curr = word;
            found = true;
            numItemsInTable++;
        } else if (curr->getWord() == word.getWord()) {
            curr->addAppearance(word.getLine(0), word.getIndex(0));
            found = true;
        } else {
            hashedLoc = (hashedLoc + 1) % currentTableSize;
        }
    }
}

/* Name: addIns
*  Purpose: add an insensitive word. For example, “Hello” is an insensitive
*  version of “hello.”
*  Arguments: A wordSensitive word, representing an insensitive word
*  Effects: adds the insensitive word to the lowercase version’s insensitive
*  appearances array
*  Returns:  none
*/ 
void wordHash::addIns(wordSensitive word) {
    bool found = false;
    
    std::string wordLower = word.getWord();
    for (size_t i = 0; i < wordLower.size(); i++) {
        wordLower[i] = std::tolower(wordLower[i]);
    }

    int hashedLoc = hashFunc(wordLower) % currentTableSize;
    while (not found) {
        wordSensitive *curr = &wordTable[hashedLoc];
        if (curr->isEmpty() and curr->isInsEmpty()) {
            wordSensitive newSensitive(wordLower);
            newSensitive.addInsAppearance(word.getLine(0), word.getIndex(0));
            *curr = newSensitive;
            found = true;
            numItemsInTable++;
        } else if (curr->getWord() == wordLower) {
            curr->addInsAppearance(word.getLine(0), word.getIndex(0));
            found = true;
        } else {
            hashedLoc = (hashedLoc + 1) % currentTableSize;
        }
    }
}

/* Name: getWordSensitive
*  Purpose: Finds and returns a wordSensitive instance from the hash table
*  Arguments: a string for the word
*  Effects: none
*  Returns: the given wordSensitive instance
*/
wordSensitive wordHash::getWordSensitive(std::string word) {
    if (word == "") {
        wordSensitive emptyWord;
        return emptyWord;
    }

    int hashedLoc = hashFunc(word) % currentTableSize;
    while (not (wordTable[hashedLoc].getWord() == word)) {
        if (wordTable[hashedLoc].isEmpty() 
            and wordTable[hashedLoc].isInsEmpty()) {

            return wordTable[hashedLoc];
        }
        hashedLoc = (hashedLoc + 1) % currentTableSize;
    }
    return wordTable[hashedLoc];
}

/* Name: contains
*  Purpose: determine if a word has been previously hashed, and therefore if 
*  the hash table already contains that word
*  Arguments: a wordSensitive, which is the word that will be checked
*  Effects: none
*  Returns: a boolean, dependent on whether the hash table contains the word
*/ 
bool wordHash::contains(std::string word) {
    int hashedLoc = hashFunc(word) % currentTableSize;
    while (not (wordTable[hashedLoc].getWord() == word)) {
        if (wordTable[hashedLoc].isEmpty()) {
            return false;
        }
        hashedLoc = (hashedLoc + 1) % currentTableSize;
    }
    return true;
}

/* Name:  expand
*  Purpose: expands the hash table’s capacity
*  Arguments: none
*  Effects: creates a new hash table with a larger capacity and rehashes the
*  old items. recycles the memory of the hash table of smaller size.
*  Returns: none
*/ 
void wordHash::expand() {
    wordSensitive *oldTable = wordTable;
    int oldTableSize = currentTableSize;
    currentTableSize = (currentTableSize * 3) + 2;
    wordTable = new wordSensitive[currentTableSize];
    numItemsInTable = 0;

    for (int i = 0; i < oldTableSize; i++) {
        wordSensitive word = oldTable[i];

        if (not word.isEmpty() or not word.isInsEmpty()) {
            insert(word);
        }
    }
    delete [] oldTable;
}