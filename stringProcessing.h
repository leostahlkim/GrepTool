/*
 *  stringProcessing.h
 *  Name: Leo Kim
 *  Date: 4/9/22
 * 
 *  Purpose: Function declaratings for the string processing program. The
 *           string processing program takes in a string and strips away
 *           any leading and trailing nonalphanumeric characters.
 */

#include <string>
#include <iostream>

std::string stripNonAlphaNum(std::string string);

bool isAlpha(char c);