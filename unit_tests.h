 /*
 *  unit_tests.h
 *  Name: Leo Kim
 *  Date: 4/9/22
 *
 *  Purpose: To implement tests that assert/check if the implementation gerp,
 *           and specfically the hash table, was correct
 */

#include "wordSensitive.h"
#include "wordHash.h"
#include "searchDir.h"
#include <cassert>

 
// tests that an empty instance of the wordSensitive class is created correctly
void test_constructor() {
   wordSensitive empty;
   assert(empty.numAppearances() == 0);
}
 
// tests that an instance of the wordSensitive class can be made when passing
// a word into the constructor
void test_secondConstructor() {
   wordSensitive test("Hello");
   assert(test.numAppearances() == 0);
}
 
// testing adding one appearance of the speciifc word
void test_addAppearance() {
   wordSensitive test("Hello");
   test.addAppearance(1, 4);
   assert(test.numAppearances() == 1);
}
 
// testing adding multiple apearences of the speciifc word
void test_addAppearanceMany() {
   wordSensitive test("Hello");
   test.addAppearance(1, 9);
   test.addAppearance(2, 21);
   test.addAppearance(5, 10);
   test.addAppearance(5, 11);
   test.addAppearance(4, 4);
   test.addAppearance(4, 6);
   assert(test.numAppearances() == 6);
}
 
// testing adding multiple appearences of a specific word, along with
// duplicate locations, which should not be added to the vector
void test_addAppearanceDuplicate() {
   wordSensitive test("Hello");
   test.addAppearance(1, 15);
   test.addAppearance(2, 8);
   test.addAppearance(5, 10);
   test.addAppearance(5, 10);
   test.addAppearance(4, 4);
   test.addAppearance(4, 4);
   assert(test.numAppearances() == 4);
}
 
// testing that the appearences, along with duplciates, are handled
// and added correctly to the appearances vector
void test_printAppearances() { // made vector and struct public for purpose
   wordSensitive test("Hello"); // of testing
   test.addAppearance(1, 9);
   test.addAppearance(2, 21);
   test.addAppearance(5, 10);
   test.addAppearance(5, 11);
   test.addAppearance(4, 4);
   test.addAppearance(4, 6);
 
   // printing the contents of the appearances vector
   // in order to determine if items were added correctly
   for (int i = 0; i < test.numAppearances(); i++) {
       std::cout << "Index: " << test.appearances[i].index
       << " Line: " << test.appearances[i].line << std::endl;
   }
}
 
// testing the getIndex function and that passing in the location
// in a vector returns the index of the word in an assumed sentence
void test_getIndex() {
   wordSensitive test("Hello");
   test.addAppearance(1, 9);
   test.addAppearance(2, 21);
   assert(test.getIndex(0) == 9);
   assert(test.getIndex(1) == 21);
}
 
// testing the getIndex function and that passing in the location
// in a vector returns the line of the word in an assumed sentence
void test_getLine() {
   wordSensitive test("Hello");
   test.addAppearance(1, 9);
   test.addAppearance(2, 21);
   assert(test.getLine(0) == 1);
   assert(test.getLine(1) == 2);
}
 

// WORD HASH TESTS

//testing inserting a word into the hash table and that it is placed 
// at the correct index
void insert_test() {
   wordHash hash;
   wordSensitive word("test");
   hash.insert(word);
   int hashedLoc = hash.hashFunc(word.getWord()) % hash.currentTableSize;
   assert(hash.wordTable[hashedLoc].getWord() == "test");
}

// testing inserting many words into the hash table
void insert_many() {
   wordHash hash;
   wordSensitive word("test");
   wordSensitive word1("abcd");
   wordSensitive word2("oewur");
   hash.insert(word);
   hash.insert(word1);
   hash.insert(word2);
   assert(hash.contains("test"));
   assert(hash.contains("abcd"));
   assert(hash.contains("oewur"));
}

// testing inserting the same word twice with different locations
void insert_sameKey() {
   wordHash hash;
   wordSensitive word("test", 1, 5);
   wordSensitive word1("test", 3, 6);
   hash.insert(word);
   hash.insert(word1);
   assert(hash.contains("test"));
}

// testing that the expansion is correctly called and implemented when
// inserting more items than the old hash table capacity could handle prior
// to expanding
void insert_withExpansion() {
   wordHash hash;
   wordSensitive word("test");
   wordSensitive word1("abcd");
   wordSensitive word2("oewur");
   wordSensitive word3("ttt");
   wordSensitive word4("rrr");
   wordSensitive word5("uuu");
   hash.insert(word);
   hash.insert(word1);
   hash.insert(word2);
   hash.insert(word3);
   hash.insert(word4);
   hash.insert(word5);
   assert(hash.currentTableSize == 20);
   assert(hash.contains("test"));
   assert(hash.contains("abcd"));
   assert(hash.contains("oewur"));
   assert(hash.contains("ttt"));
   assert(hash.contains("rrr"));
   assert(hash.contains("uuu"));
}

// a stress test with expansion, insuring that it expands and inserts
// correctly for large amounts of inserts
void insert_manyExpansion() {
   wordHash hash;
   std::string test = "t";
   for (int i = 0; i < 1000; i++) {
      wordSensitive word(test);
      hash.insert(word);
      test += "t";
   }
   assert(hash.contains("tttttttttttttttttttttt"));
   assert(hash.numItemsInTable == 1000);
}

// a stres stest for inserting duplicates, insuring that duplicates
// are handled correctly in the hash table (where duplciates are added)
// to the appearances array * IF THEY HAVE DIFFERENT LOCATIONS * 
void insert_manyDuplicates() {
   wordHash hash;
   for (int i = 0; i < 1000; i++) {
      //std::cerr << i << std::endl;
      wordSensitive word("test", 9, 19);
      hash.insert(word);
   }
   assert(hash.numItemsInTable == 1);
}

// testing the contains function of the hash table
void contains_test() {
   wordHash hash;
   wordSensitive word("test");
   hash.insert(word);
   assert(hash.contains("test"));
}

// searchDir Tests

// Tested with test.txt
void readInFile_test() {
   searchDir test;
   test.readInFile("test.txt");
   for (size_t i = 0; i < test.fileLines.size(); i++) {
      std::cerr << test.fileLines[i] << std::endl;
   }
}

// Tested with test.txt
void readInFile_wordsInHash() {
   searchDir test;
   test.readInFile("test.txt");
   assert(test.hash.contains("reading"));
   assert(test.hash.contains("searchDir"));
}

// Tested with test.txt
void readInFile_correctLineIndex() {
   searchDir test;
   test.readInFile("test.txt");
   assert(test.hash.getWordSensitive("reading").getLine(0) == 4);
   assert(test.hash.getWordSensitive("reading").getIndex(0) == 3);
   assert(test.hash.getWordSensitive("searchDir").getIndex(0) == 5);
   assert(test.hash.getWordSensitive("searchDir").getLine(0) == 6);
}

// Tested with wordSensitive.cpp
void readInFile_largerFile() {
   searchDir test;
   test.readInFile("wordSensitive.cpp");
   assert(test.hash.getWordSensitive("namespace").getLine(0) == 12);
   assert(test.hash.getWordSensitive("namespace").getIndex(0) == 11);
}

// Tested with wordSensitive.cpp
void readAllFiles_tinyData() {
   searchDir test;
   FSTree tree("/comp/15/files/proj3-test-dirs/tinyData");
   test.readAllFiles(tree);
   for (size_t i = 0; i < test.fileLines.size(); i++) {
      std::cerr << test.fileLines[i] << std::endl;
   }
}

// Tested with wordSensitive.cpp
void readAllFiles_smallGutenberg() {
   searchDir test;
   FSTree tree("/comp/15/files/proj3-test-dirs/smallGutenberg");
   
   test.readAllFiles(tree);
   
   std::cerr << test.fileLines[23445] << std::endl;
   std::cerr << test.fileLines[26] << std::endl;
   std::cerr << test.fileLines[9230] << std::endl;
   std::cerr << test.fileLines[28320] << std::endl;
   std::cerr << test.fileLines.size() << std::endl;
   
}

// Tested with wordSensitive.cpp
void readAllFiles_mediumGutenberg() {
   searchDir test;
   FSTree tree("/comp/15/files/proj3-test-dirs/mediumGutenberg");
   
   test.readAllFiles(tree);
   std::cerr << test.fileLines[23445] << std::endl;
   std::cerr << test.fileLines[26] << std::endl;
   std::cerr << test.fileLines[98230] << std::endl;
   std::cerr << test.fileLines[298320] << std::endl;
   std::cerr << test.fileLines.size() << std::endl;
}

// Tested with wordSensitive.cpp
void readAllFiles_largeGutenberg() {
   searchDir test;
   FSTree tree("/comp/15/files/proj3-test-dirs/mediumGutenberg");
   
   test.readAllFiles(tree);
   std::cerr << test.fileLines[23045] << std::endl;
   std::cerr << test.fileLines[289] << std::endl;
   std::cerr << test.fileLines[985230] << std::endl;
   std::cerr << test.fileLines[299320] << std::endl;
   std::cerr << test.fileLines.size() << std::endl;
}
