/*
 *  FSTreeTraversal.cpp
 *  Name: Leo Kim
 *  Date: 4/9/22
 *
 *  Purpose: Program that takes in a directory and traverses through it,
 *           printing out every file with its full pathway.
 */

#include <iostream>
#include "FSTree.h"
using namespace std;

void printTraversal(FSTree tree);
void printTraversal(DirNode *node, string traversal);

int main (int argc, char **argv) {

    if (argc != 2) {
        cerr << "Not a valid input" << endl;
        exit(1);
    }

    string directory = argv[1];
    FSTree dir(directory);
    printTraversal(dir);
}

/* Name: printTraversal
* Purpose: Wrapper function that ensures that the original tree is not empty
* Arguments: A tree
* Effects: calls printTraversal using the tree's root and the root's name
* Returns: none
*/
void printTraversal(FSTree tree) {
    if (not tree.isEmpty()) {
        printTraversal(tree.getRoot(), "");
    }
}

/* Name: printTraversal
* Purpose: Traverse through the tree in order to print the pathway
*          to get to a certain file
* Arguments: a pointer to a directory and the string that contains the pathway
* Effects: None
* Returns: none
*/
void printTraversal(DirNode *node, string traversal) {
    traversal += node->getName();
    if (not node->isEmpty()) {
        if (node->hasFiles()) {
            for (int i = 0; i < node->numFiles(); i++) {
                cout << traversal << "/" << node->getFile(i) << endl;
            }
        } if (node->hasSubDir()) {
            for (int i = 0; i < node->numSubDirs(); i++) {
                printTraversal(node->getSubDir(i), traversal + "/");
            }
        }
    }
}