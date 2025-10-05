#ifndef FILENAME_H
#define FILENAME_H

#include <string>
#include "Filename_AVL.h"

using namespace std;
const int DEFAULT_HEIGHT = 0;

class Filename {
    private:
        string m_filename;
        int m_value;
        Filename* m_left;
        Filename* m_right;
        int m_height;
    public:
        friend class Filename_AVL;
        
        Filename(string filename, int value) {
            m_filename = filename;
            m_value = value;
            m_left = nullptr;
            m_right = nullptr;
            m_height = DEFAULT_HEIGHT;
        }

        void setFilename(string filename) { m_filename = filename; }
        void setValue(int value) { m_value = value; }
        void setLeft(Filename* left) { m_left = left; }
        void setRight(Filename* right) { m_right = right; }
        void setHeight(int height) { m_height = height; }

        string getFilename() { return m_filename; }
        int getValue() { return m_value; };
        Filename* getLeft() { return m_left; }
        Filename* getRight() { return m_right; }
        int getHeight() { return m_height; }
};
#endif