#ifndef RATINGITEM_H
#define RATINGITEM_H

#include <string>
using namespace std;

class RatingItem {
    private:
        string m_item_name;
        int m_item_value;
        int m_item_rating;
        RatingItem* m_next;
    public:
        RatingItem();
        RatingItem(string item_name, int item_rating);
        ~RatingItem();

        void setItemName(string item_name);
        void setItemValue(int item_value);
        void setItemRating(int item_rating);
        void setNext(RatingItem* next);

        string getItemName();
        int getItemValue();
        int getItemRating();
        RatingItem* getNext();
};
#endif