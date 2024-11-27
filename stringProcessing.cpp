/*
 *  stringProcessing.cpp
 *  Name: Leo Kim
 *  Date: 4/9/22
 *
 *  Purpose: Function implementations for the string processing program. The
 *           string processing program takes in a string and strips away
 *           any leading and trailing nonalphanumeric characters.
 */

#include "stringProcessing.h"
using namespace std;

/*int main() {
    string word = "";

    while (word != "q") {
        cin >> word;
        cout << "result: " << stripNonAlphaNum(word) << endl;
    }
    
    return 0;
}*/

/* Name: stripNonAlphaNum
* Purpose: Strips the non-alpha-numeric characters from a user inputted string
* Arguments: a string that is inputted by the user
* Effects: removes all characters not in the alphabet or not a number
* Returns: the string that contains only numbers or letters
*/
string stripNonAlphaNum(string string) {

    while ((not isAlpha(string[string.size() - 1]) 
            and (string.size() != 0))) {
        string.erase(string.size() - 1, 1);
    }
    while ((not isAlpha(string[0])) and (string.size() != 0)) {
        string.erase(0, 1);
    }
    return string;  
}

/* Name: isAlpha
* Purpose: determine if a character is a lowercase letter, uppercase letter, or a number
* Arguments: a specific character from the user inputted string
* Effects: none
* Returns: a boolean dependent on whether the character is alphanumeric
		  (true if it is, false otherwise) 
*/
bool isAlpha(char c) {
    return (c > 47 and c < 58) or (c > 64 and c < 91) or (c > 96 and c < 123);
}