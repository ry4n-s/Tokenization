#include <iostream>

#include "linkedlist.hpp"
#include "hashtable.hpp"

//default constructor initializes an empty linked list and nullptr hash table
LinkedList::LinkedList() : p_head(nullptr), p_tail(nullptr), hashTable(nullptr) {}

//inserts a new word with its associated token into the linked list
bool LinkedList::insert(const std::string& word, int token) {
    //create a new node with given word and token
    LinkedListNode* newNode = new LinkedListNode(word, token);
    
    //if the list is empty, set both head and tail to this new node
    if (!p_head) {
        p_head = newNode;
        p_tail = newNode;
    } else {
        //otherwise, append the new node at the end and update tail pointer
        p_tail->p_next = newNode;
        p_tail = newNode;
    }
    return true;  //indicates that insertion was successful
}

//returns the token associated with the given word if it exists in the linked list
int LinkedList::get_token(const std::string& word) const {
    //start from the head of the list
    LinkedListNode* p_current = p_head;

    //traverse the list
    while (p_current) {
        if (p_current->data == word) return p_current->token;  //if word is found, return its token
        p_current = p_current->p_next;  //move to next node
    }
    
    return 0; //return 0 if word not found
}

//returns the word associated with the given token if it exists in the linked list
std::string LinkedList::get_word(int token) const {
    LinkedListNode* p_current = p_head;
    //traverse the list
    while (p_current) {
        if (p_current->token == token) {
            return p_current->data;  //if token is found, return its word
        }
        p_current = p_current->p_next;  //move to next node
    }
    return "";  //return an empty string if token not found
}

//destructor for the linked list, deallocates all nodes in the list
LinkedList::~LinkedList() {
    //traverses the list from the head and deletes all nodes
    while (p_head) {
        LinkedListNode* p_temp = p_head;
        p_head = p_head->p_next;
        delete p_temp;
    }
    p_tail = nullptr; 
}

//sets the hash table for the linked list
void LinkedList::set_hash_table(HashTable* ht) {
    hashTable = ht;
}
