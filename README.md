# New Rating List
## Programmer: Mark Quimba

### Description
This is a Rating List that utilizes a chaining hash table to store rated items that are inputs from the user. This program also utilizes an AVL tree in order to store files containing different rating lists.
The program would first look for a file that stores the file names of different .txt files containing lists. If this file is not present initially, upon successful program exit, the file will be created. The 
list of file names will be displayed to the terminal and user input will allow selection of a desired file. If there are no files, a new file for the list can be created and customly named from the user. There
is no limit to how many files can be created. Once a file is selected, there are numerous options that can be selected that allow manipulation of the list data. Options include: <br>
- Preview Item List: Displays the whole list to the terminal.
- Add Item To List: Which adds an item to the list based on rating. If there are multple items with the same rating, the item value will be used to place the item manually into the list.
- Remove Item From List: Removes an item from the list based on the value.
- Modify Item From List: Allows modification of an item from the list. Can modify the name of an item, the rating of the item, or both.
- Search For Item In List: Given a substring from user input, it will search for items containing the same substring (not case sensitive).
- Save List: Writes the current state of the list into the file.
- Quit: Terminates the program safely and also saves the state of the list into the file.

### Compile Instructions
1. For Windows OS, Mingw-w64 must be installed as this program uses a Makefile to build and compile the code.
2. make and g++ must be installed in order to run ```make```.
3. After running ```make``` in the directory of the code files, ```./RatingList``` will run the executable code.

### Sources
- https://cplusplus.com/reference/
- https://makefiletutorial.com/
- https://en.wikipedia.org/wiki/AVL_tree
- https://en.wikipedia.org/wiki/Hash_table
