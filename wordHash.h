/*
 *  wordHash.h
 *  Name: Leo Kim
 *  Date: 4/9/22
 *
 *  Purpose: Interface of the wordHash class.
 */

#ifndef _wordHash_H_
#define _wordHash_H_

#include "wordSensitive.h"

#include <iostream>
#include <vector>
#include <functional>
#include <string>

class wordHash
{
public:
    wordHash();
	~wordHash();
    void insert(wordSensitive word);
    wordSensitive getWordSensitive(std::string word);
    void addIns(wordSensitive word);

private:
    wordSensitive *wordTable;
    std::hash<std::string> hashFunc;
    static const int INITIAL_TABLE_SIZE = 6;
    int currentTableSize;
    int numItemsInTable;

    bool contains(std::string word);
    void expand();
};

#endif