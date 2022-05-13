#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cassert>  //assert
#include <ctype.h>
#include "BinarySearchTree.h"

#define TEST_EXERCISE3

/* *********************************************
 * Exercise 3: frequency table
 ********************************************* */

#ifdef TEST_EXERCISE3

struct Row {
    // ADD CODE: exercise 3
public:
    // Default constructor
    Row() : counter{0} {};
    
    // Constructor
    Row(std::string word) : key{word}, counter{1} {};
    
    // Destructor
    ~Row()=default;
    
    // overloaded < operator
    // sort in alphabetical order.
    bool operator<(const Row &r) const{
        return key < r.key;
    }
    
    // Overload == for assertion
    bool operator==(const Row &r) const {
        return key == r.key && counter == r.counter;
    }

    std::string key;
    int counter = 0;
    
};

// Add other stuff, if needed

// Check if char is ok or not
bool checkChar(const char c) {
    if ( std::isdigit(c) || std::isalpha(c) || (c == '\'') || (c == '-')) // Catch c == '’')
        return false;
    
    return true;
}



#endif

void exercise3() {
#ifdef TEST_EXERCISE3
    {
        // std::ifstream file("../../code/text.txt");  // contains 56 unique words
         std::ifstream file("../../code/text_long.txt"); // contains 497 unique words

        if (!file) {
            std::cout << "Couldn't open file text.txt\n";
            // std::cout << "Couldn't open file text_long.txt\n";
            return;
        }

        // ADD CODE: exercise 3
        
        BinarySearchTree<Row> freqTable;
        
        std::string key;
        int word_counter = 0;
        Row new_row;
        
        while (file >> key) {
            
            // remove not valid characters from string
            key.erase(remove_if(key.begin(), key.end(), checkChar), key.end());
            // to lower case
            std::transform(key.begin(), key.end(), key.begin(),
                [](char c){ return std::tolower(c); });
            
            BinarySearchTree<Row>::Iterator it = freqTable.find(key);
            
            if(it == freqTable.end()){
                freqTable.insert(Row(key));
                it = freqTable.begin();
            }else {
                it->counter++;
            }
            word_counter++;
            
            std::cout << "Number of words in the file = " << word_counter << std::endl;
            std::cout << "Number of unique words in the file = " << freqTable.get_count_nodes() << std::endl << std::endl;
            std::cout << "\n\n\n";
        }
        
        std::vector<Row> test;
        std::copy(freqTable.begin(), freqTable.end(), std::back_inserter(test));
        
       // std::ifstream in("../../code/frequency_table.txt");
        std::ifstream in("../../code/frequency_table_long.txt");
        std::vector<Row> facit;
        std::string word;
        int counter2;

        while (in >> word >> counter2) {
            Row newRow;
            newRow.key = word;
            newRow.counter = counter2;
            facit.push_back(newRow);
            }
        
        assert(test == facit);

    }
	assert(BinarySearchTree<Row>::get_count_nodes() == 0);
    
   
    

    std::cout << "Success!!\n";
#endif		
}
