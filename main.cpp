#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "hashtable.hpp"
#include "linkedlist.hpp"

int main() {
    //initializes hash table with a default size of 10 (arbitrary)
    int tableSize = 10;
    HashTable hashTable(tableSize);

    std::string command;
    //loop
    while (std::cin >> command) {
        
        //resizes hash table
        if (command == "M") {
            int m;
            if (!(std::cin >> m) || m <= 0) {
                std::cin.clear(); //clears any error flags
                //skips remaining bad input on this line
                char ch;
                while (std::cin.get(ch) && ch != '\n') {}
            } else {
                tableSize = m;
                hashTable.resize(m);
                std::cout << "success" << std::endl;
            }
        }

        //inserts word into hash table
        else if (command == "INSERT") {
            std::string word;
            if (!(std::cin >> word)) break;

            int token = hashTable.insert(word);
            if(token > 0) {
                hashTable.insert_token_word_mapping(token, word);
            }
            std::cout << (token > 0 ? "success" : "failure") << std::endl;
        }

        //reads from a file and inserts each word into hash table
        else if (command == "READ") {
            std::string filename;
            if (!(std::cin >> filename)) break;

            std::ifstream inputFile(filename);
            if (!inputFile) {
                std::cout << "failure" << std::endl;
                continue;
            }

            std::string word;
            int newWordsAdded = 0; //tracks how many words are added
            while (inputFile >> word) {
                if (hashTable.is_alphabetic(word)) {
                    int token = hashTable.insert(word);
                    if (token > 0) {
                        newWordsAdded++;
                    }
                }
            }
            inputFile.close();
            std::cout << (newWordsAdded > 0 ? "success" : "failure") << std::endl;
        }

        //gets the token for a word
        else if (command == "TOKENIZE") {
            std::string word;
            if (!(std::cin >> word)) break;
            int token = hashTable.retrieve(word);
            std::cout << token << std::endl;
        }

        //gets the word for a token
        else if (command == "RETRIEVE") {
            int token;
            if (!(std::cin >> token)) {
                std::cin.clear();
                char temp;
                //skips until the end of the line for invalid input
                while (std::cin.get(temp) && temp != '\n');
                std::cout << "UNKNOWN" << std::endl;
                continue;
            }
            std::string word = hashTable.retrieve_word(token);
            std::cout << (word.empty() ? "UNKNOWN" : word) << std::endl;
        }

        // Convert a string of words into tokens
        else if (command == "STOK") {
            std::string wordString;
            std::cin.ignore();
            if (!std::getline(std::cin, wordString)) break;
            std::istringstream iss(wordString);
            std::string word;
            bool firstWord = true;
            while (iss >> word) {
                if (word == "_DONE_") break; //special token to end the sequence

                int token = hashTable.retrieve(word);
                if (!firstWord) std::cout << " ";
                firstWord = false;

                std::cout << (token == -1 ? "0" : std::to_string(token));
            }
            std::cout << std::endl;
        }

        //converts a string of tokens into words
        else if (command == "TOKS") {
            std::string tokenString;
            std::cin.ignore();
            if (!std::getline(std::cin, tokenString)) break;
            std::istringstream iss(tokenString);
            int token;
            bool firstToken = true;
            while (iss >> token) {
                if (token == -1) break; //stop on the special token

                std::string word = hashTable.retrieve_word(token);
                if (!firstToken) std::cout << " ";
                firstToken = false;

                std::cout << (word.empty() ? "UNKNOWN" : word);
            }
            std::cout << std::endl;
        }

        //prints a specific chain in the hash table
        else if (command == "PRINT") {
            int k;
            if (!(std::cin >> k)) break;
            if (k <= 0 || k > tableSize) {
                std::cout << "chain is empty" << std::endl;
                continue;
            }
            hashTable.print_chain(k-1);
        }

        //breaks the loop
        else if (command == "EXIT") {
            break;
        }
    }

    return 0;
}
