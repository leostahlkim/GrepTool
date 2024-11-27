/*
 *  main.cpp
 *  Name: Leo Kim
 *  Date: 4/9/22
 *
 *  Purpose: Main function for our gerp.
 */

#include "searchDir.h"

int main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cout << "Usage: ./gerp inputDirectory outputFile\n";
    } else {
        searchDir dir(argv[1], argv[2]);
        dir.run();
    }

    return 0;
}