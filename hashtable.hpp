#ifndef _HASHTABLE_HPP_
#define _HASHTABLE_HPP_

#include <string>

class LinkedList; // Forward declaration

class HashTable {
public:
    HashTable(int table_size);
    ~HashTable();

    int insert(const std::string& key); 
    bool insert(int key, const std::string& value); //overloaded for int key
    int retrieve(const std::string& word) const;
    void print_chain(int position) const;
    bool is_alphabetic(const std::string& str);
    std::string retrieve_word(int token) const;
    int insert_and_get_index(const std::string& word);
    void resize(int newSize);
    void insert_token_word_mapping(int token, const std::string& word);
    std::string get_word_for_token(int token);
    int compute_ASCII_sum(const std::string& word) const;
    bool contains_word(const std::string& word);

private:
    int size;
    LinkedList* words_to_tokens; 
    LinkedList* tokens_to_words; 
    int next_token;
    int current_word_count;

    int hash(const std::string& word) const;
    int hash(int key) const; //overloaded for int key
};

#endif
