#pragma once

#include <iostream>
#include <iomanip>
#include <cassert>  // used in node.h

#include "dsexceptions.h"

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree {
private:
    struct Node;  // nested class defined in node.h

public:
    class Iterator;  // Exercise 2: nested class to be defined in Iterator.h

    BinarySearchTree() : root{nullptr} {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree(const BinarySearchTree &rhs) : root{clone(rhs.root)} {}

    // Constructor 
    explicit BinarySearchTree(const std::vector<Comparable>& V) {

        root = createBST(V.begin(), V.end(), nullptr); 
        
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree() {
        makeEmpty();
    }

    /**
     * Copy assignment: copy and swap idiom
     */
    BinarySearchTree &operator=(BinarySearchTree _copy) {
        std::swap(root, _copy.root);
        return *this;
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMin() const {
        if (isEmpty()) {
            throw UnderflowException{};
        }

        return findMin(root)->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMax() const {
        if (isEmpty()) {
            throw UnderflowException{};
        }

        return findMax(root)->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Comparable &x) const {
        return (contains(x, root) != nullptr);
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree(std::ostream &out = std::cout) const {
        if (isEmpty()) {
            out << "Empty tree";
        } else {
            preorder(root, out);
        }
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty() {
        root = makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable &x) {
        root = insert(x, root);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const Comparable &x) {
        root = remove(x, root);
    }



    Comparable get_parent(const Comparable& x) const
    {
       
        Node* n = contains(x, root);

        if (n && n->parent != nullptr) {
            return n->parent->element;
        }
        else return Comparable{};
        
    }



    /** Return total number of existing nodes
     *
     * Used for debug purposes
     */
    static int get_count_nodes() {
        return Node::count_nodes;
    }

    Iterator begin() {
        
        if(isEmpty())
            return end();
        
        return findMin(root);
    }
    
    Iterator end() {
        return Iterator(nullptr);
    }
    
    Iterator find(const Comparable& x) {
        return contains(x, root);
    }
    
private:
    Node *root;

    /**
     * Private member function to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Return a pointer to the node storing x.
     */

    //find_successor: returns pointer to the node storing the successor of the value stored in given node t 
    //                 if no successor then returns nullptr

     Node* find_successor(Node* t) {

        if (t->right != nullptr)
            return findMin(t->right);

        // Successor is an ancestor
        Node* p = t->parent; 
        while (p != nullptr && t == p->right) {
            t = p;
            p = p->parent; 
        }
        return p; 
    }
    
     Node* find_predecessor(Node* t) {
        if(t->left != nullptr){
            return findMax(t->left);
        }
        
        Node* p = t->parent;
        while(p != nullptr && t == p->left){
            t = p;
            p = p->parent;
        }
        
        return p; 
    }

    //Create BST function
    Node* createBST(typename std::vector<Comparable>::const_iterator begin, typename std::vector<Comparable>::const_iterator end, Node* parent) {
        if (std::distance(begin, end) == 0)
            return nullptr; 

        auto mid = begin + std::distance(begin, end) / 2; 
        Node* newNode = new Node(*mid, nullptr, nullptr, nullptr);
        newNode->parent = parent; 

        newNode->left = createBST(begin, mid, newNode); 
        newNode->right = createBST( mid + 1, end, newNode); 
        

        return newNode; 

    }


    Node *insert(const Comparable &x, Node *t) {
        if (t == nullptr) {
            t = new Node{x, nullptr, nullptr, nullptr};

        } else if (x < t->element) {
            t->left = insert(x, t->left); 
            t->left->parent = t; // set t to left parent 

        } else if (t->element < x) {
            t->right = insert(x, t->right);
            t->right->parent = t; // set t to right parent

        } else {
            ;  // Duplicate; do nothing
        }
        return t;
    }

    /**
     * Private member function to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Return a pointer to the new root of the subtree that had root x
     */
    Node *remove(const Comparable &x, Node *t) {
        if (t == nullptr) {
            return t;  // Item not found
        }
        if (x < t->element) {

            t->left = remove(x, t->left);

        } else if (t->element < x) {

            t->right = remove(x, t->right);

        } else if (t->left != nullptr && t->right != nullptr) {// Two children

            t->element = findMin(t->right)->element; // find succesor
            t->right = remove(t->element, t->right); // remove element

        } else {
            Node *oldNode = t;

            if (t->left != nullptr || t->right != nullptr) {

                (t->left != nullptr) ? t->left->parent = t->parent : t->right->parent = t->parent;
            }

            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
        return t;
    }

    /**
     * Private member function to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    Node *findMin(Node *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        if (t->left == nullptr) {
            return t;
        }

        // Tail recursion can be easily replaced by a loop
        return findMin(t->left);  // recursive call
    }

    /**
     * Private member function to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    Node *findMax(Node *t) const {
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    }

    /**
     * Private member function to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     * Return a pointer to the node storing x, if x is found
     * Otherwise, return nullptr
     */
    Node *contains(const Comparable &x, Node *t) const {
        if (t == nullptr) {
            return t;
        } else if (x < t->element) {
            return contains(x, t->left);
        } else if (t->element < x) {
            return contains(x, t->right);
        } else {
            return t;  // Match
        }
    } // in the course book, this function returns a bool
	
    /****** NONRECURSIVE VERSION*************************
    Node *contains(const Comparable &x, Node *t) const {
        while (t != nullptr) {
            if (x < t->element) {
                t = t->left;
            } else if (t->element < x) {
                t = t->right;
            } else {
                return t;  // Match
            }
        }
        return t;  // No match
    }
    *****************************************************/

    /**
     * Private member function to make subtree empty.
     */
    Node *makeEmpty(Node *t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return nullptr;
    }

    /**
     * Private member function to print a subtree rooted at t in sorted order.
     * In-order traversal is used
     */
    void inorder(Node *t, std::ostream &out) const {
        if (t != nullptr) {
            inorder(t->left, out);
            out << t->element << '\n';
            inorder(t->right, out);
        }
    }

    void preorder(Node *t, std::ostream& out, int level = 0) const {

        if (t != nullptr)
        {
            for (size_t i = 0; i < level; i++)
            {
               
                out << "  ";
                
            }

            out << t->element << std::endl;
            level++;
            preorder(t->left, out, level);
            preorder(t->right, out, level);
        }

    }


    /**
     * Private member function to clone subtree.
     */
    Node* clone(Node* t) const {

        if (t == nullptr) {
            return nullptr;
        }

        else {

            Node* temp = new Node(t->element, clone(t->left), clone(t->right));

            if (temp->left != nullptr) {

                temp->left->parent = temp;
            }

            if (temp->right != nullptr) {

                temp->right->parent = temp;
            }

            return temp;
        }
    }
};

// Include definitions of the nested classes
#include "node.h"
#include "iterator.h"
