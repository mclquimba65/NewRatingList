#ifndef UTILITIES_H
#define UTILITIES_H

#include "RatingHash.h"
#include <string>
#include <iostream>
#include <iomanip>

const int MINRATING = -100;
const int MAXRATING = 100;

const int MINMENUINPUT = 1;
const int MAXMENUINPUT = 7;

const int MINQUITINPUT = 1;
const int MAXQUITINPUT = 2;

const int MINMODIFYINPUT = 1;
const int MAXMODIFYINPUT = 3;

using namespace std;

void displayMenu();
void displayModifiedList(RatingHash* main_hash_ptr);
void displayEqualRatingItems(vector<RatingItem*> equal_rating_vector);

bool isDigit(const char char_digit);
void verifyInteger(const string string_number);

void validateMenuSelect(const int menu_input);
void validateRating(const int rating_input);
void validateValue(const int value_input, const int hash_num_elements);
void validateValueSpecial(const int value_input, vector<RatingItem*> equal_rating_vector);
void validateQuitSelect(const int quit_input);
void validateModifySelect(const int modify_select);

void previewList(RatingHash* main_hash_ptr);
void addItem(RatingHash* main_hash_ptr);
void modifyItem(RatingHash* main_hash_ptr);
void removeItem(RatingHash* main_hash_ptr);
void searchForItem(RatingHash* main_hash_ptr);
void saveList(RatingHash* main_hash_ptr);
bool quit(RatingHash* main_hash_ptr);


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
    if (menu_input < MINMENUINPUT || menu_input > MAXMENUINPUT) {
        throw runtime_error("Invalid Entry - Menu Select");
    }
}

void validateRating(const int rating_input) {
    if (rating_input < MINRATING || rating_input > MAXRATING) {
        throw runtime_error("Invalid Entry - Rating");
    }
}

void validateValue(const int value_input, const int hash_num_elements) {
    if (value_input < 1 || value_input > hash_num_elements) {
        throw runtime_error("Invalid Entry - Value");
    }
}

void validateValueSpecial(const int value_input, vector<RatingItem*> equal_rating_vector) {
    if (value_input < equal_rating_vector[0]->getItemValue() || value_input > equal_rating_vector[equal_rating_vector.size() - 1]->getItemValue() + 1) {
        throw runtime_error("Invalid Entry = Value (Special)");
    }
}

void validateQuitSelect(const int quit_input) {
    if (quit_input < MINQUITINPUT || quit_input > MAXQUITINPUT) {
        throw runtime_error("Invalid Entry - Quit Select");
    }
}

void validateModifySelect(const int modify_input) {
    if (modify_input < MINMODIFYINPUT || modify_input > MAXMODIFYINPUT) {
        throw runtime_error("Invalid Entry - Modify Select");
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

void displayEqualRatingItems(vector<RatingItem*> equal_rating_vector) {
    ios default_stream(NULL);
    default_stream.copyfmt(cout);

    cout << setfill('-') << setw(28) << right << "| " << "Equal Rated Items" << setw(28) << left << " |" << endl;
    cout.copyfmt(default_stream);

    for (int i = 0; i < equal_rating_vector.size(); i++) {
        string item_name = "-" + equal_rating_vector[i]->getItemName() + "-";
        string item_value = to_string(equal_rating_vector[i]->getItemValue()) + ".";
        cout << setw(6) << left << item_value << setw(49) << left << item_name << setw(1) << right << "(" << equal_rating_vector[i]->getItemRating() << ")" << endl;
    }

    cout << setfill('-') << setw(73) << "" << endl;
    cout.copyfmt(default_stream);
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
    cout << endl;

    string item_rating = "";
    cout << "[ Enter Item Rating ]" << endl;
    cout << "-> ";
    getline(cin, item_rating);
    cout << endl;

    try {
        verifyInteger(item_rating);
        int int_item_rating = stoi(item_rating);
        validateRating(int_item_rating);
        vector<RatingItem*> same_rating_vector = main_hash_ptr->findAllSameRatings(int_item_rating);
        if (same_rating_vector.size() != 0) {           // If there are same rated items in the list, ask for an additional value.
            displayEqualRatingItems(same_rating_vector);
            string item_value = "";
            cout << "[ Enter Item Value ]" << endl;
            cout << "-> ";
            getline(cin, item_value);
            cout << endl;
            verifyInteger(item_value);
            int int_item_value = stoi(item_value);
            validateValueSpecial(int_item_value, same_rating_vector);
            main_hash_ptr->insertItemInList(int_item_value, item_name, int_item_rating);
        }
        else {
            main_hash_ptr->insertItemInList(-1, item_name, int_item_rating);
        }
    }
    catch (runtime_error e) {
        cout << "Error: " << e.what() << endl;
    }

    displayModifiedList(main_hash_ptr);
    cout.copyfmt(default_stream);
}

void removeItem(RatingHash* main_hash_ptr) {
    if (main_hash_ptr->getNumElements() == 0) {
        cout << "Unable To Remove Item: List Empty\n" << endl;
        return;
    }
    ios default_stream(NULL);
    default_stream.copyfmt(cout);

    cout << setfill('-') << setw(73) << left << "" << endl;
    cout << "(3) Remove Item From List\n" << endl;
    cout.copyfmt(default_stream);

    main_hash_ptr->displayAllItems();
    cout << endl;

    string item_value = "";
    cout << "[ Enter Item Value ]" << endl;
    cout << "-> ";
    getline(cin, item_value);
    cout << endl;

    try {
        verifyInteger(item_value);
        int int_item_value = stoi(item_value);
        validateValue(int_item_value, main_hash_ptr->getNumElements());
        main_hash_ptr->removeItemFromList(int_item_value);
    }
    catch (runtime_error e) {
        cout << "Error: " << e.what() << endl;
    }

    displayModifiedList(main_hash_ptr);
    cout.copyfmt(default_stream);
}

void modifyItem(RatingHash* main_hash_ptr) {
    if (main_hash_ptr->getNumElements() == 0) {
        cout << "Unable To Modify Item: List Empty\n" << endl;
    }
    ios default_stream(NULL);
    default_stream.copyfmt(cout);

    cout << setfill('-') << setw(73) << left << "" << endl;
    cout << "(4) Modify Item From List\n" << endl;
    cout.copyfmt(default_stream);

    string item_value = "";
    cout << "[ Enter Item Value ]" << endl;
    cout << "-> ";
    getline(cin, item_value);
    cout << endl;

    int int_modify_item_value = -1;
    try {
        verifyInteger(item_value);
        int_modify_item_value = stoi(item_value);
        validateValue(int_modify_item_value, main_hash_ptr->getNumElements());
    }
    catch (runtime_error e) {
        cout << "Error: " << e.what() << endl;
        displayModifiedList(main_hash_ptr);
        return;
    }

    string modify_input = "";
    cout << "(1) Modify Item Name\n(2) Modify Item Rating\n(3) Modify All\n" << endl;
    cout << "[ Choose Option ]" << endl;
    cout << "-> ";
    getline(cin, modify_input);
    cout << endl;

    int int_modify_input = -1;
    try {
        verifyInteger(modify_input);
        int_modify_input = stoi(modify_input);
        validateModifySelect(int_modify_input);
    }
    catch (runtime_error e) {
        cout << "Error: " << e.what() << endl;
        displayModifiedList(main_hash_ptr);
        return;
    }

    string item_name = "";
    string item_rating = "";
    int int_item_rating = -1;
    int int_insert_item_value = -1;

    switch (int_modify_input) {
        case 1:
            cout << "[ Enter Item Name ]" << endl;
            cout << "-> ";
            getline(cin, item_name);
            cout << endl;
            int_insert_item_value = int_modify_item_value;
            int_item_rating = main_hash_ptr->getItem(int_modify_item_value)->getItemRating();
            main_hash_ptr->modifyItemFromList(int_modify_item_value, int_insert_item_value, item_name, int_item_rating);
            break;
        case 2:
            cout << "[ Enter Item Rating ]" << endl;
            cout << "-> ";
            getline(cin, item_rating);
            cout << endl;
            try {
                verifyInteger(item_rating);
                int_item_rating = stoi(item_rating);
                validateRating(int_item_rating);
                item_name = main_hash_ptr->getItem(int_modify_item_value)->getItemName();
                vector<RatingItem*> same_rating_vector = main_hash_ptr->findAllSameRatings(int_item_rating);
                if (same_rating_vector.size() != 0) {
                    displayEqualRatingItems(same_rating_vector);
                    cout << "[ Enter Item Value ]" << endl;
                    cout << "-> ";
                    getline(cin, item_value);
                    cout << endl;
                    verifyInteger(item_value);
                    int_insert_item_value = stoi(item_value);
                    validateValueSpecial(int_insert_item_value, same_rating_vector);
                    main_hash_ptr->modifyItemFromList(int_modify_item_value, int_insert_item_value, item_name, int_item_rating);
                }
                else {
                    main_hash_ptr->modifyItemFromList(int_modify_item_value, -1, item_name, int_item_rating);
                }
            }
            catch (runtime_error e) {
                cout << "Error: " << e.what() << endl;
                displayModifiedList(main_hash_ptr);
                return;
            }
            break;
        case 3:
            cout << "[ Enter Item Name ]" << endl;
            cout << "-> ";
            getline(cin, item_name);
            cout << endl;
            cout << "[ Enter Item Rating ]" << endl;
            cout << "-> ";
            getline(cin, item_rating);
            cout << endl;
            try {
                verifyInteger(item_rating);
                int_item_rating = stoi(item_rating);
                validateRating(int_item_rating);
                vector<RatingItem*> same_rating_vector = main_hash_ptr->findAllSameRatings(int_item_rating);
                if (same_rating_vector.size() != 0) {
                    displayEqualRatingItems(same_rating_vector);
                    cout << "[ Enter Item Value ]" << endl;
                    cout << "-> ";
                    getline(cin, item_value);
                    cout << endl;
                    verifyInteger(item_value);
                    int_insert_item_value = stoi(item_value);
                    validateValueSpecial(int_insert_item_value, same_rating_vector);
                    main_hash_ptr->modifyItemFromList(int_modify_item_value, int_insert_item_value, item_name, int_item_rating);
                }
                else {
                    main_hash_ptr->modifyItemFromList(int_modify_item_value, -1, item_name, int_item_rating);
                }
            }
            catch (runtime_error e) {
                cout << "Error: " << e.what() << endl;
                displayModifiedList(main_hash_ptr);
                return;
            }
            break;
        default:
            cout << "This shouldn't happen" << endl;
            break;
    }

    displayModifiedList(main_hash_ptr);
    cout.copyfmt(default_stream);
}

void searchForItem(RatingHash* main_hash_ptr) {
    ios default_stream(NULL);
    default_stream.copyfmt(cout);

    cout << setfill('-') << setw(73) << left << "" << endl;
    cout << "(5) Search For Item In List\n" << endl;
    cout.copyfmt(default_stream);

    string item_name = "";
    cout << "[ Enter Item Name/Substring ]" << endl;
    cout << "-> ";
    getline(cin, item_name);
    cout << endl;

    main_hash_ptr->displayAllSameNames(item_name);
    cout.copyfmt(default_stream);
}

void saveList(RatingHash* main_hash_ptr) {
    ios default_stream(NULL);
    default_stream.copyfmt(cout);

    cout << setfill('-') << setw(73) << left << "" << endl;
    cout << "(6) Save List\n" << endl;
    main_hash_ptr->writeToFile(FILENAME);
    cout << "List Saved!\n" << endl;

    cout.copyfmt(default_stream);
}

bool quit(RatingHash* main_hash_ptr) {
    ios default_stream(NULL);
    default_stream.copyfmt(cout);

    cout << setfill('-') << setw(73) << left << "" << endl;
    cout << "(7) Quit\n" << endl;
    cout.copyfmt(default_stream);

    main_hash_ptr->displayAllItems();
    cout << endl;

    bool return_value = false;
    bool error_encountered = false;
    do {
        cout << setfill('-') << setw(30) << right << "| " << "Finalize List" << setw(30) << left << " |" << endl;
        cout << "(1) Yes\n(2) No" << endl;
        cout.copyfmt(default_stream);
        cout << endl;

        string option_input = "";
        cout << "[ Choose Option ]" << endl;
        cout << "-> ";
        getline(cin, option_input);
        cout << endl;

        try {
            verifyInteger(option_input);
            int int_option_input = stoi(option_input);
            validateQuitSelect(int_option_input);
            if (int_option_input == 1) {
                main_hash_ptr->writeToFile(FILENAME);
                return_value = true;
            }
        }
        catch (runtime_error e) {
            cout << "Error: " << e.what() << endl;
            error_encountered = true;
        }
    } while (error_encountered);

    return return_value;
}
#endif