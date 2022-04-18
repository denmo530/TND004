#include "set.h"
#include "node.h"

int Set::Node::count_nodes = 0;  // initialize total number of existing nodes to zero

/*****************************************************
 * Implementation of the member functions             *
 ******************************************************/

// Used for debug purposes -- static member function
// Return number of existing nodes
int Set::get_count_nodes() {
    return Set::Node::count_nodes;
}

// Default constructor
Set::Set() : counter{0} {
    // IMPLEMENT before Lab1 HA
    head = new Node();
    tail = new Node(); 

    head->next = tail; 
    tail->prev = head; 

}

// Conversion constructor
Set::Set(int n) : Set{} {  // create an empty list
    // IMPLEMENT before Lab1 HA
    insert_node(tail, n);

}

// Constructor to create a Set from a sorted vector v
Set::Set(const std::vector<int>& v) : Set{} {  // create an empty list
      // IMPLEMENT before Lab1 HA
    counter = 0;
 
    for (size_t i = 0; i < v.size(); i++)
    {
        insert_node(tail, v[i]);
    }
}

// Make the set empty
void Set::make_empty() {
    // IMPLEMENT before Lab1 HA
    Node* temp = head; 

    while (temp->next != tail) {
        temp = temp->next;
        remove_node(temp->prev);
    }

    head->next = tail;
    tail->prev = head; 
}

// Destructor
Set::~Set() {
    // Member function make_empty() can be used to implement the destructor
    // IMPLEMENT before Lab1 HA
    make_empty(); // O(n)
    remove_node(head); // O(1)
    remove_node(tail); // O(1)

}

// Copy constructor
Set::Set(const Set& source) : Set{} {  // create an empty list
    // IMPLEMENT before Lab1 HA
    
    
    Node* ptr1 = source.head->next; 
    Node* ptr2 = tail; 


    while (ptr1 != source.tail) {
        insert_node(ptr2, ptr1->value);
        ptr1 = ptr1->next; 

    }

    tail = ptr2; 
}


// Copy-and-swap assignment operator
Set& Set::operator=(Set source) {
    // IMPLEMENT before Lab1 HA
    counter = source.counter; 
    std::swap(head, source.head);
    std::swap(tail, source.tail);

    return *this;
}

// Test set membership
bool Set::is_member(int val) const {
    // IMPLEMENT before Lab1 HA
    
    Node* ptr = head->next; 
    while (ptr != tail) {
        if (ptr->value == val)
            return true;
        ptr = ptr->next; 
    }

    return false;  // remove this line
}

// Test whether a set is empty
bool Set::is_empty() const {


    return (counter == 0);
}

// Return number of elements in the set
size_t Set::cardinality() const {
    return counter;
}

// Return true, if the set is a subset of b, otherwise false
// a <= b iff every member of a is a member of b
bool Set::less_than(const Set& b) const {
    // IMPLEMENT
    Node* ptr1 = this->head->next;
    Node* ptr2 = b.head->next;
    
    while(ptr1 != this->tail && ptr2 != b.tail) {
        if (ptr1->value < ptr2->value){
            return  false;
        }
        
        if(ptr1->value == ptr2->value){
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;        }
        else {
            ptr2 = ptr2->next;
        }
    }
    
    return ptr1 == tail;
}



// Modify *this such that it becomes the union of *this with Set S
// Add to *this all elements in Set S (repeated elements are not allowed)
Set& Set::operator+=(const Set& S) {
    // IMPLEMENT
    Node* ptr1 = head->next;
    Node* ptr2 = S.head->next;
    
    while( ptr1 != tail && ptr2 != S.tail) {
        if(ptr1->value < ptr2->value){
            ptr1 = ptr1->next;
        }else if(ptr1->value == ptr2->value) {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }else if(ptr1->value > ptr2->value){
            insert_node(ptr1, ptr2->value);
            ptr2 = ptr2->next;
        }
    }
    
    // Add whatever is left in Set S
    while (ptr2->next != nullptr) {
        insert_node(ptr1, ptr2->value);
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

    return *this;
} 

// Modify *this such that it becomes the intersection of *this with Set S
Set& Set::operator*=(const Set& S) {
    // IMPLEMENT
    
    Node* ptr1 = head->next;
    Node* ptr2 = S.head->next;
    
    while(ptr1 != tail && ptr2 != S.tail){
        if(ptr1->value == ptr2->value) {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }else if (ptr1->value > ptr2->value){
            ptr2 = ptr2->next;
        }
        else if (ptr1->value < ptr2->value) {
            ptr1 = ptr1->next;
            remove_node(ptr1->prev);
        }
    }
    
    // Remove rest of *this if there are more values
    while(ptr1->next != nullptr) {
        ptr1 = ptr1->next;
        remove_node(ptr1->prev);
    }

    return *this;
}

// Modify *this such that it becomes the Set difference between Set *this and Set S
Set& Set::operator-=(const Set& S) {
    // IMPLEMENT
    Node* ptr1 = head->next;
    Node* ptr2 = S.head->next;
    
    while(ptr1 != tail && ptr2 != S.tail){
        if (ptr1->value == ptr2->value) {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
            remove_node(ptr1->prev);
        }else if(ptr1->value < ptr2->value){
            ptr1 = ptr1->next;
        } else if(ptr1->value > ptr2->value){
            ptr2 = ptr2->next; 
        }
    }
    return *this;
}

/* ******************************************** *
 * Private Member Functions -- Implementation   *
 * ******************************************** */

// If you add any private member functions to class Set then write the implementation here


void Set::write_to_stream(std::ostream& os) const {
    if (is_empty()) {
        os << "Set is empty!";
    } else {
        Set::Node* temp{head->next};

        os << "{ ";
        while (temp != tail) {
            os << temp->value << " ";
            temp = temp->next;
        }
        os << "}";
    }
}


// Insert a new Node storing val after the Node pointed by p
void Set::insert_node(Node* p, int val) {
    // IMPLEMENT before Lab1 HA
    Node* newNode = new Node(val, p, p->prev);
    p->prev = p->prev->next = newNode;
    
    counter++;

    
    
}

// Remove the Node pointed by p
void Set::remove_node(Node* p) {
    // IMPLEMENT before Lab1 HA
    if (p == nullptr) {
        return;
    }

    if (head == p) {
        head = p->next; 
    }

    if (p->next != nullptr) {
        p->next->prev = p->prev; 
    }

    if(p->prev != nullptr)
    {
       p->prev->next = p->next; 
    }
    

    delete p;
    counter--; 
}

