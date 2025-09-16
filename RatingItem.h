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

RatingItem::RatingItem() {
    m_item_name = "";
    m_item_value = 0;
    m_item_rating = 0;
    m_next = nullptr;
}

RatingItem::RatingItem(string item_name, int item_rating) {
    m_item_name = item_name;
    m_item_value = 0;
    m_item_rating = item_rating;
    m_next = nullptr;
}

RatingItem::~RatingItem() {
    m_item_name = "";
    m_item_value = 0;
    m_item_rating = 0;
    m_next = nullptr;
}

void RatingItem::setItemName(string item_name) {
    m_item_name = item_name;
}

void RatingItem::setItemValue(int item_value) {
    m_item_value = item_value;
}

void RatingItem::setItemRating(int item_rating) {
    m_item_rating = item_rating;
}

void RatingItem::setNext(RatingItem* next) {
    m_next = next;
}

string RatingItem::getItemName() {
    return m_item_name;
}

int RatingItem::getItemValue() {
    return m_item_value;
}

int RatingItem::getItemRating() {
    return m_item_rating;
}

RatingItem* RatingItem::getNext() {
    return m_next;
}
#endif