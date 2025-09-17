#include <iostream>
#include <string>
#include "RatingHash.h"
#include "utilities.h"

using namespace std;

bool driverSwitch(RatingHash* main_hash_ptr);

int main() {
    bool list_present = false;
    if (FILENAME != "") {
        list_present = true;
    }
    RatingHash main_hash(list_present);
    bool end_program = false;
    
    RatingHash* main_hash_ptr = &main_hash;
    while (!end_program) {
        end_program = driverSwitch(main_hash_ptr);
    }
}

bool driverSwitch(RatingHash* main_hash_ptr) {
    ios default_stream(NULL);
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
    catch (runtime_error e) {
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
                break;
            default:
                terminate_program = quit(main_hash_ptr);
                break;
        }
    }

    return terminate_program;
}