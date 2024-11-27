/*
 *  searchDir.h
 *  Name: Leo Kim
 *  Date: 4/9/22
 *
 *  Purpose: Interface for the searchDir class.
 */

#ifndef _searchDir_H_
#define _searchDir_H_

#include "wordHash.h"
#include "FSTree.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <string>
#include <sstream>

class searchDir
{
public:
    searchDir(std::string directory, std::string oFile);
    ~searchDir();

    void run();


private:
    wordHash hash;
    std::vector<std::string> fileLines;
    std::vector<std::string> traversalPaths;
    FSTree traversalTree;
    std::ofstream outputFile;

    void readInFile(std::string filename);
    void readAllFiles();
    void readAllFiles(DirNode *node, std::string traversal);
    std::string stripNonAlphaNum(std::string string);
    bool isAlpha(char c);
    void printLine(int line, int index);
    bool printAppearances(std::string word);
    bool printInsensitive(std::string word);
};

#endif