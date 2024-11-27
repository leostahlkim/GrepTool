/*
 *  testMain.cpp
 *  Name: Leo Kim
 *  Date: 4/9/22
 *
 *  Purpose: TESTING MAIN
 */

#include "searchDir.h"

int main () {
    
    //searchDir test("/comp/15/files/proj3-test-dirs/smallGutenberg", 
         //           "a.txt");
    //searchDir test("/comp/15/files/proj3-test-dirs/mediumGutenberg", 
                    //"a.txt");
    searchDir test("/comp/15/files/proj3-test-dirs/largeGutenberg", 
                    "a.txt");
    //searchDir test("/comp/15/files/proj3-test-dirs/tinyData", 
           //         "a.txt");
    //searchDir test("/h/lkim11/cs15/proj3/testDir", 
      //             "a.txt");
    //FSTree tree("/h/lkim11/cs15/proj3/testDir");
    //FSTree tree("/comp/15/files/proj3-test-dirs/smallGutenberg");
    //FSTree tree("/comp/15/files/proj3-test-dirs/mediumGutenberg");
    //FSTree tree("/comp/15/files/proj3-test-dirs/largeGutenberg");
    //test.readAllFiles();
    //test.printLine(6, 10);
    //wordSensitive word = test.hash.getWordSensitive("");
    //test.printLine(word.getLine(28), word.getIndex(28));
    //test.printAppearances("apple");
    //std::cerr << test.fileLines.size() << "\n";


    test.run();

    return 0;
}