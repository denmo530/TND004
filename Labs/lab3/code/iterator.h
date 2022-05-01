#pragma once

/* **********************************************************
 * Class to represent a bi-directional iterator for BSTs     *
 * Bi-directional iterators can be moved in both directions, *
 * increasing and decreasing order of items keys             *
 * ***********************************************************/

template <typename Comparable>
class BinarySearchTree<Comparable>::Iterator {
public:
    // Some properties for Iterator  -- so that Iterator can be used with STL-algorithms
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = Comparable;
    using pointer           = Comparable*;  // or also value_type*
    using reference         = Comparable&;  // or also value_type&

    /* ****************************************************************** */

    // Exercise 2: ADD CODE   
    friend class BinarySearchTree;

    //Default Constructor
    Iterator();

    //Overloaded operators
    Comparable& operator*() const { return current->element; }
    Comparable* operator->() const { return &current->element; }
    bool operator==(const Iterator &it) const { return current == it.current; }
    bool operator!=(const Iterator &it) const { return (!(current == it.current)); }
    
    Iterator& operator++(int) {  //pos-increment
        Iterator tmp = *this;
        ++(*this);
        return tmp;
        
    }
    
    Iterator& operator--(int) { //pos-decrement
        Iterator tmp = *this;
        --(*this);
        return tmp;
        
    }
    
    Iterator& operator++() { //pre-increment
        current = bst->find_successor(current);
        return *this;
        
    }
    
    Iterator& operator--() { //pre-decrement
        current = bst->find_predecessor(current);
        return *this; 
    }

    
private:
    Node* current;
    BinarySearchTree* bst;

    // Non-public constructor, create iterator given a pointer
    Iterator(Node* t = nullptr) : current{t} {}
};
