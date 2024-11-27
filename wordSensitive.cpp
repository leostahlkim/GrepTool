/*
 *  wordSensitive.cpp
 *  Name: Leo Kim
 *  Date: 4/9/22
 *
 *  Purpose: Implementation of the wordSensitive class.
        The wordSensitive class stores a word and both its case sensitive
        and case insensitive appearances.
 */

#include "wordSensitive.h"
using namespace std;

wordSensitive::wordSensitive() {}

/* Name: Constructor
*  Purpose: To create a wordSensitive of a word without a location and index
*  Arguments: a string, representing the word
*  Effects: creates a wordSensitive containing the word
*  Returns: none
*/ 
wordSensitive::wordSensitive(std::string inputWord) {
    word = inputWord;
}

/* Name: Third Constructor
*  Purpose: Create a wordSensitive of a word that has a location and an index
*  Arguments: a string, representing a word, and two integers, one representing
*  the location, and the other the index of the word found when reading in 
*  from a file 
*  Effects: creates a wordSensitive of a word, with the word’s location in
*  a file
*  Returns: none
*/ 
wordSensitive::wordSensitive(std::string inputWord, int line, int index) {
    word = inputWord;
    addAppearance(line, index);
}

wordSensitive::~wordSensitive() {}

/* Name: addAppearence
*  Purpose: To add an appearance, meaning a word’s location and index, if 
*  the same word had been previously hashed
*  Arguments: two integers, representing the word’s location and index
*  Effects: adds the word to the vector containing all of the locations of 
*  the appearances of a word
*  Returns: none
*/ 
void wordSensitive::addAppearance(int line, int index) {
    if (isEmpty() or (appearances[appearances.size() - 1].index != index)) {
        lineIndex temp;
        temp.line = line;
        temp.index = index;
        appearances.push_back(temp);
    }
}

/* Name: addInsAppearence
*  Purpose: To add an insensitive appearance, meaning a word’s location and
*  index, if the same word toLowered had been previously hashed (“Hello” and 
*  “hello”)
*  Arguments: two integers, representing the word’s location and index
*  Effects: adds the insensitive word to the vector containing all of the
*  locations of the 
*	     appearances of a word
*  Returns: none
*/
void wordSensitive::addInsAppearance(int line, int index) {
    if (isInsEmpty() or 
        (insAppearances[insAppearances.size() - 1].index != index)) {
        lineIndex temp;
        temp.line = line;
        temp.index = index;
        insAppearances.push_back(temp);
    }
}

/* Name: getIndex
*  Purpose: gets the index of a word from the appearances vector given the
*  location
*	       of the word in the vector
*  Arguments: an integer, representing the location
*  Effects: find the index of a word from its original file
*  Returns: the index
*/ 
int wordSensitive::getIndex(int location) {
    return appearances[location].index;
}

/* Name: getInsIndex
*  Purpose: gets the index of an insensitive word from the insensitive
*  appearances vector given
*	       the location of the word in the vector 
*  Arguments: an integer, representing the location
*  Effects: find the index of a word from its original file
*  Returns: the index
*/
int wordSensitive::getInsIndex(int location) {
    return insAppearances[location].index;
}

/* Name: getLine
*  Purpose: gets the line of a word from its original file given the location
*  it is in 
*	      appearances array
*  Arguments: an integer, representing the location in the array
*  Effects: finds the line of a word from its original file
*  Returns: the line
*/
int wordSensitive::getLine(int location) {
    return appearances[location].line;
}

/* Name: getInsLine
*  Purpose: gets the line of an insensitive word from its original file given
*  the location it is in 
*	      insensitive appearances array
*  Arguments: an integer, representing the location in the array
*  Effects: finds the line of a word from its original file
*  Returns: the line
*/ 
int wordSensitive::getInsLine(int location) {
    return insAppearances[location].line;
}

/* Name: numAppearences
*  Purpose: find the frequency a word appears after processing all files
*  Arguments: none
*  Effects: none
*  Returns: the size of the appearances vector
*/ 
int wordSensitive::numAppearances() {
    return appearances.size();
}

/* Name: numInsAppearences
*  Purpose: find the frequency an insensitive word appears after processing all
*  files
*  Arguments: none
*  Effects: none
*  Returns: the size of the insensitive appearances vector
*/ 
int wordSensitive::numInsAppearances() {
    return insAppearances.size();
}

/* Name: getWord
*  Purpose: To get the word from a wordSensitive
*  Arguments: none
*  Effects: none
*  Returns: a string, representing the word
*/ 
string wordSensitive::getWord() {
    return word;
}

/* Name: isEmpty
*  Purpose: determines if the appearances vector is empty
*  Arguments: none
*  Effects: none
*  Returns: a boolean dependent on whether the appearances vector is empty
*/ 
bool wordSensitive::isEmpty() {
    return (appearances.size() == 0);
}

/* Name: isInsEmpty
*  Purpose: determines if the insensitive appearances vector is empty
*  Arguments: none
*  Effects: none
*  Returns: a boolean dependent on whether the insensitive appearances vector
*  is empty
*/
bool wordSensitive::isInsEmpty() {
    return (insAppearances.size() == 0);
}