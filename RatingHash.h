#ifndef RATINGHASH_H
#define RATINGHASH_H

#include <string>
#include <vector>

const int NUMBUCKETS = 20;
const std::string FILENAME = "";

class RatingHash {
    private:
        RatingItem** m_rating_hash;
        int m_num_elements;

        int hashFunction(const int item_rating);
        void updateAllValues();
    public:
        RatingHash(bool list_present);
        ~RatingHash();
        int getNumElements();
        void readFromFile(const string FILENAME);
        void displayAllItems();
        void displayAllSameNames(const string item_substring);
        vector<RatingItem*> findAllSameRatings(const int item_rating);
        bool nameExists(const string item_name);
        void insertItemInList(int item_value, string item_name, int item_rating);
        void modifyItemFromList(int remove_item_value, int insert_item_value, string item_name, int item_rating);
        void removeItemFromList(int item_value);
        void writeToFile(string FILENAME);
};
#endif