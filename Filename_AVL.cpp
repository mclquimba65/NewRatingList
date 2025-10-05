#include "Filename_AVL.h"

using namespace std;

Filename_AVL::Filename_AVL() {
    m_avl = nullptr;
    readFromSpecialFile();
}

Filename_AVL::~Filename_AVL() {
    deleteTree(m_avl);
}

int Filename_AVL::retrieveHeight(Filename* root) {
    if (root == nullptr)
        return -1;
    
    int left_height = -1, right_height = -1;
    if (root->m_left != nullptr)
        left_height = root->m_left->m_height;
    if (root->m_right != nullptr)
        right_height = root->m_right->m_height;
    
    return (max(left_height, right_height) + 1);
}

Filename* Filename_AVL::leftRotation(Filename* root) {
    Filename* right_ptr = root->m_right;
    Filename* right_left_ptr = root->m_right->m_left;

    right_ptr->m_left = root;
    root->m_right = right_left_ptr;

    root->m_height = retrieveHeight(root);
    right_ptr->m_height = retrieveHeight(right_ptr);
    return right_ptr;
}

Filename* Filename_AVL::rightRotation(Filename* root) {
    Filename* left_ptr = root->m_left;
    Filename* left_right_ptr = root->m_left->m_right;

    left_ptr->m_right = root;
    root->m_left = left_right_ptr;

    root->m_height = retrieveHeight(root);
    left_ptr->m_height = retrieveHeight(left_ptr);
    return left_ptr;
}

Filename* Filename_AVL::balanceAVLHelper(Filename* root) {
    if (root == nullptr)
        return root;
    
    int left_height = retrieveHeight(root->m_left);
    int right_height = retrieveHeight(root->m_right);
    int height_deltas = left_height - right_height;
    if (height_deltas < -1) {                                                                   // Right height > Left height
        if (retrieveHeight(root->m_right->m_right) > retrieveHeight(root->m_right->m_left)) {   // Right's right height > Right's left height
            root = leftRotation(root);
        }
        else {                                                                                  // Right's right height < Right's left height
            root->m_right = rightRotation(root->m_right);
            root = leftRotation(root);
        }
    }
    else if (height_deltas > 1) {                                                                                      // Left height > Right height
        if (retrieveHeight(root->m_left->m_left) > retrieveHeight(root->m_left->m_right)) {     // Left's left height > Left's right height
            root = rightRotation(root);
        }
        else {                                                                                  // Left's left height < left's right height
            root->m_left = leftRotation(root->m_left);
            root = rightRotation(root);
        }
    }

    return root;
}

Filename* Filename_AVL::findInOrderSuccessor(Filename* root) {
    while (root->m_left != nullptr) {
        root = root->m_left;
    }
    return root;
}

Filename* Filename_AVL::insertInAVLHelper(Filename& new_file, Filename* root) {
    if (root == nullptr) {
        Filename* new_file_ptr = new Filename(new_file.m_filename, new_file.m_value);
        root = new_file_ptr;
    }
    else {          // Tree traversal
        if (new_file.getValue() < root->m_value)        // Traverse left
            root->m_left = insertInAVLHelper(new_file, root->m_left);
        else if (new_file.getValue() > root->m_value)   // Traverse right
            root->m_right = insertInAVLHelper(new_file, root->m_right);
    }
    root->m_height = retrieveHeight(root);
    root = balanceAVLHelper(root);
    return root;
}

Filename* Filename_AVL::removeFromAVLHelper(const int value, Filename* root) {
    if (root == nullptr)
        return root;

    if (value < root->m_value)                          // Traverse left
        root->m_left = removeFromAVLHelper(value, root->m_left);
    else if (value > root->m_value)                     // Traverse right
        root->m_right = removeFromAVLHelper(value, root->m_right);
    else {                                              // Value is found
        if (root->m_left == nullptr && root->m_right == nullptr) {      // Has no children
            delete root;
            root = nullptr;
        }
        else if (root->m_left != nullptr && root->m_right != nullptr) { // Has two children
            Filename* in_order_successor = findInOrderSuccessor(root->m_right);
            root->m_filename = in_order_successor->m_filename;
            root->m_value = in_order_successor->m_value;
            root->m_right = removeFromAVLHelper(root->m_value, root->m_right);
        }
        else {
            Filename* to_remove = root;                                 // Has 1 child
            if (root->m_left != nullptr) {
                root = root->m_left;
                delete to_remove;
            }
            else {
                root = root->m_right;
                delete to_remove;
            }
        }
    }

    root->m_height = retrieveHeight(root);
    root = balanceAVLHelper(root);
    return root;
}

void Filename_AVL::displayInOrderHelper(Filename* root) {
    if (root == nullptr)
        return;
    displayInOrderHelper(root->m_left);
    string line = "";
    line = to_string(root->m_value) + " " + root->m_filename;
    cout << line << endl;
    displayInOrderHelper(root->m_right);
}

void Filename_AVL::writeToSpecialFileHelper(Filename* root, ofstream& o_file_stream) {
    if (root == nullptr)
        return;
    writeToSpecialFileHelper(root->m_left, o_file_stream);
    string line = "";
    line = to_string(root->m_value) + " " + root->m_filename;
    o_file_stream << endl;
    o_file_stream << line;
    writeToSpecialFileHelper(root->m_right, o_file_stream);
}

void Filename_AVL::returnFilenamesHelper(Filename* root, vector<string>& filenames_vector) {
    if (root == nullptr)
        return;
    returnFilenamesHelper(root->m_left, filenames_vector);
    filenames_vector.push_back(root->m_filename);
    returnFilenamesHelper(root->m_right, filenames_vector);
}

void Filename_AVL::deleteTree(Filename* root) {
    if (root == nullptr)
        return;
    deleteTree(root->m_left);
    deleteTree(root->m_right);
    delete root;
}



void Filename_AVL::insertInAVL(Filename& new_file) {
    m_avl = insertInAVLHelper(new_file, m_avl);
}

void Filename_AVL::removeFromAVL(const int value) {
    removeFromAVLHelper(value, m_avl);
}

void Filename_AVL::displayInOrder() {
    displayInOrderHelper(m_avl);
}

void Filename_AVL::writeToSpecialFile() {
    ofstream special_file_output(SPECIAL_FILE);
    special_file_output << "WARNING: DO NOT MODIFY THIS FILE MANUALLY";
    writeToSpecialFileHelper(m_avl, special_file_output);
    special_file_output.close();
}

void Filename_AVL::readFromSpecialFile() {
    ifstream special_file_input;
    special_file_input.open(SPECIAL_FILE);
    if (!special_file_input.is_open())
        return;

    string line = "", filename = "";
    int value_counter = 1;
    getline(special_file_input, line);      // Skip the first line of the file

    while (getline(special_file_input, line)) {
        istringstream special_input_stream(line);
        getline(special_input_stream, filename, ' ');       // Skip value
        getline(special_input_stream, filename, '\n');

        Filename new_file(filename, value_counter);
        insertInAVL(new_file);
        value_counter++;
    }
    special_file_input.close();
}

vector<string> Filename_AVL::returnFilenames() {
    vector<string> filenames_vector;
    returnFilenamesHelper(m_avl, filenames_vector);
    return filenames_vector;
}