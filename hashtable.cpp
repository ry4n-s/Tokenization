#include <iostream>
#include <string>

#include "hashtable.hpp"
#include "linkedlist.hpp"

//constructor initialize hash table with a given size
HashTable::HashTable(int table_size) 
    : size(table_size), next_token(1), current_word_count(0) {
    //creates arrays of linked lists to store word-token and token-word mappings
    words_to_tokens = new LinkedList[table_size];
    tokens_to_words = new LinkedList[table_size];

    //initializes each linked list with a reference to this hash table
    for (int i = 0; i < table_size; ++i) {
        words_to_tokens[i].set_hash_table(this);
        tokens_to_words[i].set_hash_table(this);
    }
    
    //exits the program if allocation fails
    if (!words_to_tokens || !tokens_to_words) {
        exit(1);
    }
}

//destructor deallocates memory
HashTable::~HashTable() {
    delete[] words_to_tokens;
    delete[] tokens_to_words;
}

//inserts word into hash table and return associated token
int HashTable::insert(const std::string& word) {
    //ensures word is alphabetic
    if (!is_alphabetic(word)) {
        return -1;
    }

    //ensures word isn't already present
    if (contains_word(word)) {
        return -1;
    }

    //gets hash position for the word and adds it to the chain
    int position = hash(word);
    LinkedList& chain = words_to_tokens[position];
    int token = next_token++;
    chain.insert(word, token);
    
    //also insert into the tokens_to_words list
    tokens_to_words[token % size].insert(word, token);
    
    return token;
}

//inserts a word-token pair directly into hash table
bool HashTable::insert(int token, const std::string& word) {
    int position = hash(token) % size;
    tokens_to_words[position].insert(word, token);
    return true;
}

//retrieves token for a given word
int HashTable::retrieve(const std::string& word) const {
    int position = hash(word);

    //ensures position is valid
    if (position < 0 || position >= size) {
        return 0; 
    }

    const LinkedList& chain = words_to_tokens[position];
    int token = chain.get_token(word);

    //returns token if found, else 0
    return token != -1 ? token : 0;
}

//retrieves word for a given token
std::string HashTable::retrieve_word(int token) const {
    //ensures token is valid
    if (token < 1 || token >= next_token) {
        return "UNKNOWN";
    }

    int position = token % size;
    LinkedList& chain = tokens_to_words[position];
    std::string word = chain.get_word(token);

    //returns word if found, else "UNKNOWN"
    return word.empty() ? "UNKNOWN" : word;
}

//checks if given string is alphabetic
bool HashTable::is_alphabetic(const std::string& str) {
    for (char c : str) {
        if (!std::isalpha(c)) {
            return false;
        }
    }
    return true;
}

//hash function for string
int HashTable::hash(const std::string& word) const {
    int hash_value = 0;
    for (char c : word) {
        hash_value += c;
    }
    return hash_value % size;
}

//hash function for integer
int HashTable::hash(int key) const {
    return key % size;
}

//prints the elements of a chain given a position
void HashTable::print_chain(int position) const {
    if (position < 0 || position >= size) {
        std::cerr << "chain is empty" << std::endl;
        return;
    }

    LinkedList::LinkedListNode* p_current = words_to_tokens[position].p_head;
    if (!p_current) {
        std::cout << "chain is empty" << std::endl;
        return;
    }

    //prints ASCII sum for each word in chain
    while (p_current) {
        std::cout << compute_ASCII_sum(p_current->data);
        p_current = p_current->p_next;
        if (p_current) std::cout << " ";
    }
    std::cout << std::endl;
}

//inserts word and returns its index in the chain
int HashTable::insert_and_get_index(const std::string& word) {
    if (!is_alphabetic(word)) {
        return -1;
    }

    int position = hash(word);
    LinkedList& chain = words_to_tokens[position];

    if (contains_word(word)) {
        return -1;
    }

    int index = 1;
    LinkedList::LinkedListNode* p_current = chain.p_head;
    while (p_current) {
        index++;
        p_current = p_current->p_next;
    }

    chain.insert(word, index);
    return index;
}

//resizes the hash table
void HashTable::resize(int newSize) {
    LinkedList* newTable = new LinkedList[newSize];
    
    for (int i = 0; i < size; i++) {
        LinkedList::LinkedListNode* p_current = words_to_tokens[i].p_head;
        while (p_current) {
            int newPosition = hash(p_current->data) % newSize;
            newTable[newPosition].insert(p_current->data, p_current->token);
            p_current = p_current->p_next;
        }
    }

    delete[] words_to_tokens;
    words_to_tokens = newTable;
    size = newSize;
}

//inserts a token-word mapping
void HashTable::insert_token_word_mapping(int token, const std::string& word) {
    tokens_to_words[token % size].insert(word, token);
}

//retrieves a word for a given token
std::string HashTable::get_word_for_token(int token) {
    LinkedList& chain = tokens_to_words[token % size];
    LinkedList::LinkedListNode* p_current = chain.p_head;
    while (p_current) {
        if (p_current->token == token) {
            return p_current->data;
        }
        p_current = p_current->p_next;
    }
    return "";
}

//computes ASCII sum for a given word
int HashTable::compute_ASCII_sum(const std::string& word) const {
    int sum = 0;
    for (char c : word) {
        sum += c;
    }
    return sum;
}

//checks if a word is contained within the hash table
bool HashTable::contains_word(const std::string& word) {
    int position = hash(word);
    if (position < 0 || position >= size) {
        return false;
    }
    const LinkedList& chain = words_to_tokens[position];
    LinkedList::LinkedListNode* p_current = chain.p_head;
    while (p_current) {
        if (p_current->data == word) {
            return true;
        }
        p_current = p_current->p_next;
    }
    return false;
}
