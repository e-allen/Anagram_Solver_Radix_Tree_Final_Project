#include "Radix.h"
#include <algorithm>

//Struct to hold a word and its score.
#ifndef TESTING
struct ScoredWord {
    std::string word;
    int score;
};

/*----MAIN-------*/
//Main 
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std:: cerr << "Error: No input string provided." << std::endl;
        std:: cout << "Usage: " << argv[0] << " \"your rack letters here\"" << std::endl;
        std:: cout << "Do not include spaces\blank tiles." << std::endl;
        return 1;
    }
    std::string rack = argv[1];

    Radix tree;

    //Load the dictionary file into the radix tree
    std::ifstream file("scrabble_dictionary.txt");
    std::string word;
    if (file.is_open()) {
        while (getline(file, word)) {
            tree.insert(word);
        }
        file.close();
    } else {
        std::cout << "Error: Unable to load dictionary file";
        return 1;
    }

    //Ensure rack letters are uppercase.
    for (auto &c : rack) {
        c = toupper(c);
    }

    //Find all possible words from the given rack.
    std::vector<std::string> words = tree.find_words(rack);

    //Calculate the score for each word.
    std::vector<ScoredWord> scored_words;
    for (const std::string& w : words) {
        scored_words.push_back({w, tree.get_word_score(w)});
    }

    //Sort the words in descending order based on score.
    std::sort(scored_words.begin(), scored_words.end(), [](const ScoredWord& a, const ScoredWord& b) {
        return a.score > b.score;
    });

    //Print the sorted list of words and their scores.
    std::cout << "\033[1;36m********************************************\033[0m" << std::endl;
    std::cout << "\033[1;36m|                                          |\033[0m" << std::endl;
    std::cout << "\033[1;36m|              ANAGRAM SOLVER              |\033[0m" << std::endl;
    std::cout << "\033[1;36m|                                          |\033[0m" << std::endl;
    std::cout << "\033[1;36m********************************************\033[0m" << std::endl;
    std::cout << "\033[1;35m--------------------------------------------\033[0m" << std::endl;
    std::cout << "\033[1;35m Words that can be formed from the letters: \033[0m" << std::endl;
    std::cout << "\033[1;35m                  " << rack << std::endl;
    std::cout << "\033[1;35m--------------------------------------------\033[0m" << std::endl;
    for (const auto& pair : scored_words) {
        std::cout << pair.word << " (Score: " << pair.score << ")" << std::endl;
    }
    std::cout << "\033[1;35m--------------------------------------------\033[0m" << std::endl;
    return 0;
}
#endif // TESTING