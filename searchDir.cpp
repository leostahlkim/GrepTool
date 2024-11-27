/*
 *  searchDir.cpp
 *  Name: Leo Kim
 *  Date: 4/9/22
 *
 *  Purpose: Implementation of the searchDir class. Purpose is to read in and
    process filesand the paths to the files. Also contains the main driver
    /command loop of the code, which processes the user's commands and 
    determines whether to search for sensitive words or not, for example
    ("hello" vs "Hello").
 */

#include "searchDir.h"

/* Name: SearchDir constructor
*  Purpose: To read all files and open an output file
*  Arguments: a string which is a directory’s name and a string which
*		is the output file’s name
*  Effects: Creates a temp FSTree using the directory’s name passed in
*  Returns: none
*/ 
searchDir::searchDir(std::string directory, std::string oFile) {
    FSTree temp(directory);
    traversalTree = temp;
    readAllFiles();
    
    outputFile.open(oFile);
    if (not outputFile.is_open()) {
        std::cerr << "Error: could not open file ";
        std::cerr << oFile << std::endl;
        exit(1);
    }
}

/* Name: Destructor
*  Purpose: Closes the output file, if it was opened correctly
*  Arguments: none
*  Effects: closes output file
*  Returns: none
*/ 
searchDir::~searchDir() {
    if (outputFile.is_open()) {
        outputFile.close();
    }
}

/* Name: Wrapper function for readAllFiles
*  Purpose: Determine if the directory is empty, and if it isn’t then 
*  call private read all files
*  Arguments: None
*  Effects: calls readAllFiles to actually process the files
*  Returns: none
*/ 
void searchDir::readAllFiles() {
    if (not traversalTree.isEmpty()) {
        readAllFiles(traversalTree.getRoot(), "");
    }
}

/* Name: readAllFiles
*  Purpose: to process the files and find the pathway to a file
*  Arguments: A pointer to the root of the passed in input directory, 
*  and a string which begins empty
*  Effects: Determines the pathway to files and adds them to a string to save
*  the traversal to that file. Calls readInFile to read the file found at 
*  the end of the traversal.
*  Returns: none
*/ 
void searchDir::readAllFiles(DirNode *node, std::string traversal) {
    traversal += node->getName();
    if (not node->isEmpty()) {
        if (node->hasSubDir()) {
            for (int i = 0; i < node->numSubDirs(); i++) {
                readAllFiles(node->getSubDir(i), traversal + "/");
            }
        } if (node->hasFiles()) {
            for (int i = 0; i < node->numFiles(); i++) {
                readInFile(traversal + "/" + node->getFile(i));
            }
        }
    }
}

/* Name: readInFile
*  Purpose: To open the files found in readAllFiles. Once opened, it processes
*	       each word in the file and keeps track of number of lines processed.
*	       Then, organizes words processed by calling appropriate helper
*          functions.
*  Arguments: A string, which is the name of the file that is to be processed.
*  Effects: Traverses through the passed-in file and processes each word by
*  calling hash helper
*	     functions
*  Returns: none
*/ 
void searchDir::readInFile(std::string filename) {
    std::ifstream file;
    file.open(filename);
    std::string line;
    int lineNumber = 0;
    fileLines.push_back(filename);

    if (not file.is_open()) {
        std::cerr << "Error: could not open file ";
        std::cerr << filename << std::endl;
        exit(1);
    }
    
    while (getline(file, line)) {
        lineNumber++;
        
        std::istringstream currLine(line);
        while (not currLine.eof()) {
            std::string word;
            currLine >> word;

            wordSensitive wordCase(stripNonAlphaNum(word), 
            lineNumber, fileLines.size());

            hash.insert(wordCase);
            hash.addIns(wordCase);
        }
        fileLines.push_back(line);
    }
    file.close();
}

/* Name: stripNonAlphaNum
* Purpose: Strips the non-alpha-numeric characters from a user inputted string
* Arguments: a string that is inputted by the user
* Effects: removes all characters not in the alphabet or not a number
* Returns: the string that contains only numbers or letters
*/
std::string searchDir::stripNonAlphaNum(std::string string) {

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
* Purpose: determine if a character is a lowercase letter, uppercase letter,
* or a number
* Arguments: a specific character from the user inputted string
* Effects: none
* Returns: a boolean dependent on whether the character is alphanumeric
		  (true if it is, false otherwise) 
*/
bool searchDir::isAlpha(char c) {
    return (c > 47 and c < 58) or (c > 64 and c < 91) or (c > 96 and c < 123);
}

/* Name: printAppearences
*  Purpose: to print the given line of the file with the correct file pathway
*  Arguments: an int representing the line number and an int representing its
*  index in the array of file lines
*  Effects: none
*  Returns: none
*/ 
void searchDir::printLine(int line, int index) {
    outputFile << fileLines[index - line] << ":";
    outputFile << line << ": " << fileLines[index] << std::endl;
}

/* Name: printAppearences
*  Purpose: to print the appearances of a word, meaning the locations, if 
*  the user’s word has a frequency higher than one once the files 
*  are processed    
*  Arguments: a string representing the user’s word
*  Effects: none
*  Returns: a boolean, dependent on if the word has a frequency higher
*  than one
*/ 
bool searchDir::printAppearances(std::string word) {
    wordSensitive temp = hash.getWordSensitive(word);

    for (int i = 0; i < temp.numAppearances(); i++) {
        printLine(temp.getLine(i), temp.getIndex(i));
    }
    return not temp.isEmpty();
}

/* Name: printInsensitive
*  Purpose: Print the insensitive appearances/locations of a word, if there
*  are any. For example, “Hello” would be an insensitive appearance of 
*  “hello.”
*  Arguments: a string representing the user’s word
*  Effects:  none
*  Returns: a boolean, dependent on if the word and its insensitive versions
*  have a frequency higher than one
*/ 
bool searchDir::printInsensitive(std::string word) {
    for (size_t i = 0; i < word.size(); i++) {
        word[i] = std::tolower(word[i]);
    }
    
    wordSensitive temp = hash.getWordSensitive(word);

    for (int i = 0; i < temp.numInsAppearances(); i++) {
        printLine(temp.getInsLine(i), temp.getInsIndex(i));
    }

    return not temp.isInsEmpty();
}

/* Name: run
*  Purpose: contains the main query loop for the gerp executable. Asks the
*  user for their command and processes it, along with the word they wish 
*  to search for.
*  Arguments: none
*  Effects: runs the correct version of gerp dependent on the user’s command
*  Returns: none
*/ 
void searchDir::run() {
    std::string input;
    bool fileDone = false;
    std::cout << "Query? ";

    while (not fileDone and std::cin >> input) {

        if (input == "@q" or input == "@quit") {
            fileDone = true;
        } else if (input == "@f") {
            std::cin >> input;
            outputFile.close();

            outputFile.open(input);
            if (not outputFile.is_open()) {
                std::cerr << "Error: could not open file ";
                std::cerr << input << std::endl;
                exit(1);
            }
        } else if (input == "@i" or input == "@insensitive") {
            std::cin >> input;
            if (not printInsensitive(stripNonAlphaNum(input))) {
                outputFile << stripNonAlphaNum(input) << " Not Found.\n";
            }
        }
        else {
            if (not printAppearances(stripNonAlphaNum(input))) {
                outputFile << stripNonAlphaNum(input)
                << " Not Found. Try with @insensitive or @i.\n";
            }
        }
        if (not fileDone) {
            std::cout << "Query? ";
        }
    }
    std::cout << "Goodbye! Thank you and have a nice day.\n";
}