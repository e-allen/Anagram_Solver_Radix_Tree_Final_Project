#ifndef ANAGRAMSOLVER_H__
#define ANAGRAMSOLVER_H__

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>


// Declaration of Radix class
class Radix {
public:
    //Construct a new Radix object.
    Radix(); 
    //Deconstruct the Radix object.
    ~Radix(); //Deconstruct the Radix object.

     //Inserts a word (key) into the radix tree.
    void insert(const std::string& key); 
    //Searches for a word (key) in the radix tree. Returns true if word exists, false otherwise.
    bool search(const std::string& key); 
     //Finds all words in the tree that can be formed from the letters in the rack. Returns a vector of words.
    std::vector<std::string> find_words(const std::string& rack);
    //Calculates the scrabble score for the given word (word). Returns integer score of word.
    int get_word_score(const std::string& word); 

private:
    //Declaration of Node struct.
    //Each node stores a part of the key and pointers to its children.
    struct Node {
        // Label on the edge leading to this node from its parent.
        std::string key_part;
        // Flag to indicate if a word ends at this node.
        bool is_end_of_word;
        // A map to store children. The key is the first character of the child's key_part, and the value is the a pointer to the child node.
        std::map<char, Node*> children;
        // Constructor for Node.
        Node(const std::string& part = "", bool is_word = false)
            :key_part(part), is_end_of_word(is_word) {}
        // Deconstructor to recursively delete all child nodes to prevent memory leaks.
        ~Node(){
            // Iterate through all children and delete them recursively.
            for (auto const& pair : children) {
                delete pair.second;
            }
        }
    };
    Node* root; //The root of the radix tree.
    //Recursive helper function to insert a key.
    void insert_helper(Node* node, const std::string& key);
    //Recursive helper function to find valid words from a rack.
    void find_words_helper(Node* node, std::string current_word, std::map<char, int> rack, std::vector<std::string>& result);
    //Get frequency of characters in a string, for scoring.
    std::map<char, int> get_freq(const std::string& s);
};

#endif 