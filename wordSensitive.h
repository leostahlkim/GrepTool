/*
 *  wordSensitive.h
 *  Name: Leo Kim
 *  Date: 4/9/22
 *
 *  Purpose: Interface of the wordSensitive class.
 */

#ifndef _wordSensitive_H_
#define _wordSensitive_H_

#include <iostream>
#include <vector>

class wordSensitive
{
public:
    wordSensitive();
    wordSensitive(std::string inputWord);
    wordSensitive(std::string inputWord, int line, int index);
    ~wordSensitive();

    void addAppearance(int line, int index);
    void addInsAppearance(int line, int index);
    int getIndex(int location);
    int getInsIndex(int location);
    int getLine(int location);
    int getInsLine(int location);
    int numAppearances();
    int numInsAppearances();
    std::string getWord();
    bool isEmpty();
    bool isInsEmpty();

private:
    struct lineIndex {
        int line;
        int index;
    };

    std::string word;
    std::vector<lineIndex> appearances;
    std::vector<lineIndex> insAppearances;
};

#endif