#include <iostream>
#include <string>
#include "RatingHash.h"
#include "utilities.h"
#include "Filename_AVL.h"

using namespace std;

bool driverSwitch(RatingHash* main_hash_ptr, Filename_AVL* file_tree_ptr);
string filenameSwitch(Filename_AVL* file_tree_ptr);

int main() {
    // Ask for filenames here
    Filename_AVL file_tree;
    Filename_AVL* file_tree_ptr = &file_tree;
    string filename = "invalid";
    do {
        filename = filenameSwitch(file_tree_ptr);
        if (filename == "exit")
            exit(0);
    } while (filename == "invalid");

    RatingHash main_hash(filename);
    bool end_program = false;
    
    RatingHash* main_hash_ptr = &main_hash;
    while (!end_program) {
        end_program = driverSwitch(main_hash_ptr, file_tree_ptr);
    }
}

bool driverSwitch(RatingHash* main_hash_ptr, Filename_AVL* file_tree_ptr) {
    ios default_stream(nullptr);
    default_stream.copyfmt(cout);

    displayMenu();

    string switch_select = "";
    int int_switch_select = -1;
    bool error_encountered = false;
    bool terminate_program = false;
    cout << "[ Enter Option ]" << endl;
    cout << "-> ";
    getline(cin, switch_select);
    try {
        verifyInteger(switch_select);
        int_switch_select = stoi(switch_select);
        validateMenuSelect(int_switch_select);
    }
    catch (runtime_error& e) {
        cout << "Error: " << e.what() << endl;
        error_encountered = true;
    }

    if (!error_encountered) {
        switch (int_switch_select) {
            case 1:
                previewList(main_hash_ptr);
                break;
            case 2:
                addItem(main_hash_ptr);
                break;
            case 3:
                removeItem(main_hash_ptr);
                break;
            case 4:
                modifyItem(main_hash_ptr);
                break;
            case 5:
                searchForItem(main_hash_ptr);
                break;
            case 6:
                saveList(main_hash_ptr);
                saveFilenames(file_tree_ptr);
                break;
            default:
                terminate_program = quit(main_hash_ptr);
                saveFilenames(file_tree_ptr);
                break;
        }
    }

    return terminate_program;
}

string filenameSwitch(Filename_AVL* file_tree_ptr) {
    ios default_stream(nullptr);
    default_stream.copyfmt(cout);

    vector<string> filename_vector = file_tree_ptr->returnFilenames();
    string switch_select = "";
    string filename = "invalid";
    int int_switch_select = -1;
    bool error_encountered = false;

    displayFilenamesMenu(filename_vector);

    cout << "[ Select Filename ]" << endl;
    cout << "-> ";
    getline(cin, switch_select);
    try {
        verifyInteger(switch_select);
        int_switch_select = stoi(switch_select);
        validateFilenamesSelect(int_switch_select, filename_vector);
    }
    catch (runtime_error& e) {
        cout << "Error: " << e.what() << endl;
        error_encountered = true;
    }

    if (!error_encountered) {
        if (int_switch_select == (filename_vector.size() + 2)) {        // If the option selected was to exit program
            filename = "exit";
        }
        else if (int_switch_select == (filename_vector.size() + 1)) {   // If the option selected was to create new file
            addFile(file_tree_ptr, filename, filename_vector);
        }
        else {                                                          // A valid filename was selected
            filename = filename_vector[int_switch_select - 1];
        }
    }

    return filename;
}