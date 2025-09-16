#include "RatingHash.h"
#include "RatingItem.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

RatingHash::RatingHash(bool list_present) {
    m_rating_hash = new RatingItem*[NUMBUCKETS];
    for (int i = 0; i < NUMBUCKETS; i++) {
        m_rating_hash[i] = nullptr;
    }
    m_num_elements = 0;
    if (list_present) {
        readFromFile(FILENAME);
    }
}

RatingHash::~RatingHash() {
    RatingItem* deletion_ptr = nullptr;
    RatingItem* next_node_ptr = nullptr;
    for (int i = 0; i < NUMBUCKETS; i++) {
        deletion_ptr = m_rating_hash[i];
        while (deletion_ptr != nullptr) {
            next_node_ptr = deletion_ptr->getNext();
            delete deletion_ptr;
            deletion_ptr = next_node_ptr;
        }
    }
    delete[] m_rating_hash;

    
}

vector<RatingItem*> RatingHash::findAllSameRatings(const int item_rating) {
    vector<RatingItem*> same_rating_vector;
    int hash_key = hashFunction(item_rating);
    RatingItem* traversal_ptr = m_rating_hash[hash_key];
    while (traversal_ptr != nullptr) {
        if (traversal_ptr->getItemRating() == item_rating) {
            same_rating_vector.push_back(traversal_ptr);
        }
        traversal_ptr = traversal_ptr->getNext();
    }

    return same_rating_vector;
}

void RatingHash::updateAllValues() {
    int value = 1;
    RatingItem* update_value_ptr = nullptr;
    for (int i = 0; i < NUMBUCKETS; i++) {
        update_value_ptr = m_rating_hash[i];
        while (update_value_ptr != nullptr) {
            update_value_ptr->setItemValue(value);
            value++;
        }
    }
}

int RatingHash::hashFunction(const int item_rating) {
    if (item_rating == 100) {
        return 0;
    }
    else {
        return abs(static_cast<int>(floor(item_rating / 10.0)) - 9);
    }
}

void RatingHash::readFromFile(const string FILENAME) {
    ifstream file_input;
    file_input.open(FILENAME);
    if (!file_input.is_open()) {
        cout << "Reading \"" << FILENAME << "\" Failed..." << "\"" << endl;
        cout << "Terminating Program..." << endl;
        exit(0);
    }

    string word = "", line = "";
    int value_counter = 1;
    while (word != "1." && !file_input.eof()) {
        file_input.ignore(1024, '\n');
        file_input >> word;
    }

    RatingItem* item_ptr = nullptr;
    int new_hash_value = -1, current_hash_value = -1;
    while (!file_input.eof()) {
        RatingItem* new_item = new RatingItem();
        getline(file_input, line);

        istringstream input_stream(line);
        getline(input_stream, word, '-');
        getline(input_stream, word, '-');

        new_item->setItemName(word);

        getline(input_stream, word, '(');
        getline(input_stream, word, ')');

        new_item->setItemRating(stoi(word));
        new_item->setItemValue(value_counter);

        new_hash_value = hashFunction(new_item->getItemRating());

        if (current_hash_value != new_hash_value) {              // Checks if new hash == current hash. If not then move to the new bucket and add node to the table.
            current_hash_value = new_hash_value;
            m_rating_hash[current_hash_value] = new_item;
            item_ptr = m_rating_hash[current_hash_value];
        }
        else {                                                   // If new hash == current hash, then just add to the end of the bucket.
            item_ptr->setNext(new_item);
            item_ptr = item_ptr->getNext();
        }

        m_num_elements++;
        value_counter++;
    }
    file_input.close();
}

void RatingHash::insertItemInList(int item_value, string item_name, int item_rating) {
    RatingItem* new_item = new RatingItem(item_name, item_rating);
    int hash_key = hashFunction(item_rating);
    RatingItem* traversal_ptr = m_rating_hash[hash_key];
    RatingItem* previous_ptr = nullptr;

    if (item_value > 0) {
        while ((traversal_ptr != nullptr) && (traversal_ptr->getItemValue() != item_value)) {
            previous_ptr = traversal_ptr;
            traversal_ptr = traversal_ptr->getNext();
        }
        if (previous_ptr == nullptr) {                          // Inserting at head.
            new_item->setNext(m_rating_hash[hash_key]);
            m_rating_hash[hash_key] = new_item;
        }
        else if (traversal_ptr != nullptr) {                    // Middle of the bucket.
            new_item->setNext(traversal_ptr);
            previous_ptr->setNext(new_item);
        }
        else {                                                  // If value is not found.
            previous_ptr->setNext(new_item);
        }
    }
    else {
        while ((traversal_ptr != nullptr) && (traversal_ptr->getItemRating() > item_rating)) {
            previous_ptr = traversal_ptr;
            traversal_ptr = traversal_ptr->getNext();
        }
        if (previous_ptr == nullptr) {                          // Inserting at head.
            new_item->setNext(m_rating_hash[hash_key]);
            m_rating_hash[hash_key] = new_item;
        }
        else if (traversal_ptr != nullptr) {                    // Middle of the bucket.
            new_item->setNext(traversal_ptr);
            previous_ptr->setNext(new_item);
        }
        else {                                                  // If value is not found.
            previous_ptr->setNext(new_item);
        }
    }

    updateAllValues();
    m_num_elements++;
}

void RatingHash::removeItemFromList(int item_value) {
    int hash_key = -1;
    bool hash_key_found = false;
    for (int i = NUMBUCKETS - 1; i >= 0; i--) {                 // Find the bucket containing the value in question
        if (m_rating_hash[i] != nullptr) {
            if (item_value >= m_rating_hash[i]->getItemValue()) {
                hash_key = i;
                hash_key_found = true;
                break;
            }
        }
    }

    RatingItem* traversal_ptr = m_rating_hash[hash_key];
    RatingItem* previous_ptr = nullptr;

    while ((traversal_ptr != nullptr) && (item_value != traversal_ptr->getItemValue())) {
        previous_ptr = traversal_ptr;
        traversal_ptr = traversal_ptr->getNext();
    }
    if (traversal_ptr == nullptr) {
        cout << "This shouldn't happen..." << endl;
        return;
    }
    if (previous_ptr == nullptr) {                              // Removing head.
        m_rating_hash[hash_key] = traversal_ptr->getNext();
    }
    else {                                                      // Removing anywhere other than head.
        previous_ptr->setNext(traversal_ptr->getNext());
    }

    delete traversal_ptr;

    updateAllValues();
    m_num_elements--;
}

void RatingHash::modifyItemFromList(int remove_item_value, int insert_item_value, string item_name, int item_rating) {
    removeItemFromList(remove_item_value);
    insertItemInList(insert_item_value, item_name, item_rating);
}

void RatingHash::displayAllItems() {
    RatingItem* traversal_ptr = nullptr;
    for (int i = 0; i < NUMBUCKETS; i++) {
        traversal_ptr = m_rating_hash[i];
        while (traversal_ptr != nullptr) {
            string temp_item_name = "-" + traversal_ptr->getItemName() + "-";
            string temp_item_value = to_string(traversal_ptr->getItemValue()) + ".";
            cout << setw(6) << left << temp_item_value << setw(49) << temp_item_name << setw(1) << right << "(" << traversal_ptr->getItemRating() << ")" << endl;
            traversal_ptr = traversal_ptr->getNext();
        }
    }
}

void RatingHash::displayAllSameNames(const string item_substring) {
    RatingItem* traversal_ptr = nullptr;
    for (int i = 0; i < NUMBUCKETS; i++) {
        traversal_ptr = m_rating_hash[i];
        while (traversal_ptr != nullptr) {
            string temp_item_name = traversal_ptr->getItemName();
            string temp_item_substring = item_substring;
            // Convert item name and substring to be upper case and compare.
            transform(temp_item_name.begin(), temp_item_name.end(), temp_item_name.begin(), ::toupper);
            transform(temp_item_substring.begin(), temp_item_substring.end(), temp_item_substring.begin(), ::toupper);
            if (temp_item_name.find(temp_item_substring) != string::npos) {     // If the substring is found within the name, display the name of the item.
                temp_item_name = "-" + traversal_ptr->getItemName() + "-";
                string temp_item_value = to_string(traversal_ptr->getItemValue()) + ".";
                cout << setw(6) << left << temp_item_value << setw(49) << temp_item_name << setw(1) << right << "(" << traversal_ptr->getItemRating() << ")" << endl;
            }
            traversal_ptr = traversal_ptr->getNext();
        }
    }
}

void RatingHash::writeToFile(const string FILENAME) {
    ofstream file_output(FILENAME);
    file_output << "\nScale: [-100, 100]\n" << setfill(' ') << endl;

    RatingItem* traversal_ptr = nullptr;
    for (int i = 0; i < NUMBUCKETS; i++) {
        traversal_ptr = m_rating_hash[i];
        while (traversal_ptr != nullptr) {
            string temp_item_name = "-" + traversal_ptr->getItemName() + "-";
            string temp_item_value = to_string(traversal_ptr->getItemValue()) + ".";
            file_output << setw(7) << left << temp_item_value << setw(49) << temp_item_name << setw(1) << right << "(" << traversal_ptr->getItemRating() << ")" << endl;
            traversal_ptr = traversal_ptr->getNext();
        }
    }
}

int RatingHash::getNumElements() {
    return m_num_elements;
}