//Author: Erin Allen
//CU ID: eral9820
//Anagram Solver for Word Games Using a Radix Tree.

#include "Radix.h"

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

//Constructor: Initializes the radix tree with an empty root node.
Radix::Radix() : root(new Node()) {}

//Deconstructor: Destroys all dynamically allocated nodes.
Radix::~Radix() {
    delete root;
}

//Insert function: calls helper function
void Radix::insert(const std::string& key) {
    insert_helper(root, key);
}

//Recursive helper function to insert a key.
void Radix::insert_helper(Node* node, const std::string& key) {
    //If the key is empty, the entire word is placed in the tree.
    if (key.empty()) {
        node->is_end_of_word = true;
        return;
    }
    /*If no existing edge matches the first character of the key,
    create new child node to store the rest of the key.*/
    if (node->children.find(key[0]) == node->children.end()) {
        node->children[key[0]] = new Node(key, true);
        return;
    }
    Node* child = node->children[key[0]];
    std::string child_key = child->key_part;

    //Find the longest common prefix between the key and the child's edge.
    int i = 0;
    while (i < key.length() && i < child_key.length() && key[i] == child_key[i]) {
        i++;
    }

    /*If the entire child's edge is a prefix of the key.
    Continue inserting the rest of the key from the child node.*/
    if (i == child_key.length()) {
        insert_helper(child, key.substr(i));
    }

    //If the key and the child's edge diverge. Split and create a new internal node.
    else {
        Node* new_child = new Node(child_key.substr(0, i), false);
        node->children[key[0]] = new_child;

        /*The old child is now a decendent of the new internal node and its key is 
        shortened to the part that was not common.*/
        child->key_part = child_key.substr(i);
        new_child->children[child_key[i]] = child;

        //When there are characters left in the key, create another new node.
        if (i < key.length()) {
            new_child->children[key[i]] = new Node(key.substr(i), true);
        } else {
            //key was common prefix, new node is end of word.
            new_child->is_end_of_word = true; 
        }
    }
}

//Searches the tree for a specific key.
bool Radix::search(const std::string& key){
    Node* node = root;
    int i = 0;
    while (i < key.length()) {
        //No matching edge found from the current node.
        if(node->children.find(key[i]) == node->children.end()) {
            return false;
        }
        Node* child = node->children[key[i]];
        std::string child_key = child->key_part;

        //Compare the rest of the key against the edge.
        for (int j = 0; j < child_key.length(); j++) {
            if (i >= key.length() || key[i] != child_key[j]) {
                return false; //Does not match
            }
            i++;
        }
        node = child; //Move to the next node.
    }
    //The entire key was consumed, check if its a valid word.
    return node->is_end_of_word;
}

//Get character frequencies from a string.
std::map<char, int> Radix::get_freq(const std::string& s) {
    std::map<char, int> freq;
    for (char c : s) {
        freq[c]++;
    }
    return freq;
}

//Recursive helper function to find all words that can be made with the letters in the rack.
void Radix::find_words_helper(Node* node, std::string current_word, std::map<char, int> rack, std::vector<std::string>& result) {
    //If the current node marks the end of a word, add it to results.
    if (node->is_end_of_word && !current_word.empty()) {
        if (std::find(result.begin(), result.end(), current_word) == result.end()) {
            result.push_back(current_word);
        }
    }

    //Check children by trying to use letters from the rack.
    for (auto const& pair : rack) {
        char letter = pair.first;
        int count = pair.second;
        if (count > 0) {
            if (node->children.count(letter)){
                Node* child = node->children[letter];
                std::string edge = child->key_part;
                std::map<char, int> temp_rack = rack;

                //Check if there are enough letters in the rack to traverse this edge.
                bool possible = true;
                for (char c : edge) {
                    if (temp_rack[c] > 0) {
                        temp_rack[c]--;
                    } else {
                        possible = false;
                        break;
                    }
                }
                //If we can traverse the edge, continue the search recursively.
                if (possible) {
                    find_words_helper(child, current_word + edge, temp_rack, result);
                }
            }
        }
    }
}

//Start the word finding process.
std::vector<std::string> Radix::find_words(const std::string& rack_str) {
    std::vector<std::string> result;
    std::map<char, int> rack = get_freq(rack_str);
    find_words_helper(root, "", rack, result);
    return result;
}

//Calculates the score of a word with letter values.
int Radix::get_word_score(const std::string& word) {
    int score = 0;
    //Scrabble letter scores.
    std::map<char, int> letter_scores = {
        {'A', 1}, {'E', 1}, {'I', 1}, {'O', 1}, {'U', 1}, {'L', 1}, {'N', 1}, {'S', 1}, {'R', 1}, {'T', 1},
        {'D', 2}, {'G', 2},
        {'B', 3}, {'C', 3}, {'M', 3}, {'P', 3},
        {'F', 4}, {'H', 4}, {'V', 4}, {'W', 4}, {'Y', 4},
        {'K', 5},
        {'J', 8}, {'X', 8},
        {'Q', 10}, {'Z', 10},
    };
    for (char c : word) {
        score += letter_scores[std::toupper(c)];
    }
    return score;
}
