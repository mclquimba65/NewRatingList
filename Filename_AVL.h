#ifndef FILENAME_AVL
#define FILENAME_AVL

#include "Filename.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

const string SPECIAL_FILE = "DO_NOT_MODIFY.txt";

class Filename_AVL {
    public:
        Filename_AVL();
        ~Filename_AVL();

        void insertInAVL(Filename& new_file);
        void removeFromAVL(const int value);
        void displayInOrder();
        void writeToSpecialFile();
        void readFromSpecialFile();
        vector<string> returnFilenames();
    private:
        Filename* m_avl;

        Filename* insertInAVLHelper(Filename& new_file, Filename* root);
        Filename* removeFromAVLHelper(const int value, Filename* root);
        Filename* balanceAVLHelper(Filename* root);
        Filename* findInOrderSuccessor(Filename* root);
        Filename* leftRotation(Filename* root);
        Filename* rightRotation(Filename* root);
        int retrieveHeight(Filename* root);
        void displayInOrderHelper(Filename* root);
        void writeToSpecialFileHelper(Filename* root, ofstream& o_file_stream);
        void returnFilenamesHelper(Filename* root, vector<string>& filenames_vector);
        void deleteTree(Filename* root);
};
#endif