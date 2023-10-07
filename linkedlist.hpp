#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <string>

class HashTable;  // Forward declaration

class LinkedList {
public:
    LinkedList();                               
    ~LinkedList();                              

    bool insert(const std::string& word, int token);
    int get_token(const std::string& word) const;       
    std::string get_word(int token) const;              
    void set_hash_table(HashTable* ht);                  

    class LinkedListNode {
    public:
        std::string data;
        int token;
        LinkedListNode* p_next;


        //constructor for LinkedListNode
        LinkedListNode(const std::string& word, int idx)
            : data(word), token(idx), p_next(nullptr) {}

    private:
    };

    HashTable* hashTable;  


    LinkedListNode* p_head; 
    LinkedListNode* p_tail;
};

#endif 
