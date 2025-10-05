#ifndef RATINGHASH_H
#define RATINGHASH_H

#include <string>
#include <vector>
#include "RatingItem.h"

const int NUMBUCKETS = 20;

using namespace std;

class RatingHash {
    private:
        RatingItem** m_rating_hash;
        int m_num_elements;
        string m_filename;

        int hashFunction(const int item_rating);
        void updateAllValues();
    public:
        RatingHash(string filename);
        ~RatingHash();
        int getNumElements();
        void readFromFile(string filename);
        void displayAllItems();
        void displayAllSameNames(const string item_substring);
        vector<RatingItem*> findAllSameRatings(const int item_rating);
        bool nameExists(const string item_name);
        void insertItemInList(int item_value, string item_name, int item_rating);
        void modifyItemFromList(int remove_item_value, int insert_item_value, string item_name, int item_rating);
        void removeItemFromList(int item_value);
        void writeToFile();
        RatingItem* getItem(const int item_value);
};
#endif