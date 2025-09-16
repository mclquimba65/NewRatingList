#ifndef UTILITIES_H
#define UTILITIES_H

#include "RatingHash.cpp"
#include <string>
#include <iostream>

const int MINRATING = -100;
const int MAXRATING = 100;

using namespace std;

void displayMenu();
void displayQuit();
void displayModifiedList(RatingItem* main_hash_ptr);

bool isDigit(const char char_digit);
void verifyInteger(const string string_number);

void validateMenuSelect(const int menu_input);
void validateRating(const int rating_input);
void validateValue(const int value_input, const int hash_num_elements);
void validateQuitSelect(const int quit_input);

void previewList(RatingHash* main_hash_ptr);
void addItem(RatingHash* main_hash_ptr);
void modifyItem(RatingHash* main_hash_ptr);
void removeItem(RatingHash* main_hash_ptr);
void searchForItem(RatingHash* main_hash_ptr);
void saveList(RatingHash* main_hash_ptr);


bool isDigit(const char char_digit) {
    if (char_digit >= '0' && char_digit <= '9') {
        return true;
    }
    return false;
}

void verifyInteger(const string string_number) {
    bool is_integer = true;
    int verify_start = 0;
    if (string_number.empty()) {
        is_integer = false;
    }
    if ((string_number[0] == '0') && (string_number.length() > 1)) {
        is_integer = false;
    }
    if (string_number[0] == '-') {
        if (string_number.length() < 2) {
            is_integer = false;
        }
        else {
            verify_start = 1;
        }
    }
    if (is_integer) {
        for (int i = verify_start; i < string_number.length(); i++) {
            if (!isDigit(string_number[i])) {
                is_integer = false;
                break;
            }
        }
    }

    if (!is_integer) {
        throw runtime_error("Invalid Entry - Integer");
    }
}

void validateMenuSelect(const int menu_input) {
    if (menu_input < 1 || menu_input > 7) {
        throw runtime_error("Invalid Entry - Menu Select");
    }
}

void validateRating(const int rating_input) {
    if (rating_input < MINRATING || rating_input > MAXRATING) {
        throw runtime_error("Invalid Entry - Rating");
    }
}

void validateValue(const int value_input, const int hash_num_elements) {
    if (value_input < 0 || value_input > hash_num_elements) {
        throw runtime_error("Invalid Entry - Value");
    }
}

void validateQuitSelect(const int quit_input) {
    if (quit_input < 1 || quit_input > 2) {
        throw runtime_error("Invalid Entry - Quit Select");
    }
}

void displayMenu() {
    ios default_stream(NULL);
    default_stream.copyfmt(cout);

    cout << setfill('-') << setw(35) << right << "| " << "MENU" << setw(34) << left << " |" << endl;
    cout.copyfmt(default_stream);

    cout << "(1) Preview Item List\n(2) Add Item To List\n(3) Remove Item From List\n(4) Modify Item From List\n(5) Search For Item In List\n(6) Save List\n (7) Quit" << endl;
    cout << endl;
}

void displayModifiedList(RatingHash* main_hash_ptr) {
    ios default_stream(NULL);
    default_stream.copyfmt(cout);

    cout << setfill('-') << setw(29) << right << "| " << "New Rating List" << setw(29) << left << " |" << endl;
    cout.copyfmt(default_stream);

    main_hash_ptr->displayAllItems();

    cout << setfill('-') << setw(73) << left << "" << endl;
    cout.copyfmt(default_stream);
    cout << "\n\n" << endl;
}

void previewList(RatingHash* main_hash_ptr) {
    ios default_stream(NULL);
    default_stream.copyfmt(cout);

    cout << setfill('-') << setw(73) << left << "" << endl;
    cout << "(1) Preview Item List\n" << endl;
    cout.copyfmt(default_stream);

    main_hash_ptr->displayAllItems();

    cout << setfill('-') << setw(73) << left << "" << endl;
    cout.copyfmt(default_stream);
    cout << "\n\n" << endl;
}

void addItem(RatingHash* main_hash_ptr) {
    ios default_stream(NULL);
    default_stream.copyfmt(cout);

    cout << setfill('-') << setw(73) << left << "" << endl;
    cout << "(2) Add Item To List\n" << endl;
    cout.copyfmt(default_stream);

    string item_name = "";
    cout << "[ Enter Item Name ]" << endl;
    cout << "-> ";
    getline(cin, item_name);

    string item_rating = "";
    cout << "[ Enter Item Rating ]" << endl;
    cout << "-> ";
    getline(cin, item_rating);

    try {
        verifyInteger(item_rating);
        int int_item_rating = stoi(item_rating);
        validateRating(int_item_rating);
        main_hash_ptr->insertItemInList(-1, item_name, int_item_rating);
    }
    catch (runtime_error e) {
        cout << "Error: " << e.what() << endl;
    }

    displayModifiedList(main_hash_ptr);
}

void removeItem(RatingHash* main_hash_ptr) {
    
}
#endif