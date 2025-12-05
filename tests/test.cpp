#include "gtest/gtest.h"
#include "Radix.h"
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <map>

TEST(RadixTree, InsertAndSearch) {
    Radix tree;
    tree.insert("HELLO");
    tree.insert("WORLD");
    ASSERT_TRUE(tree.search("HELLO"));
    ASSERT_TRUE(tree.search("WORLD"));
    ASSERT_FALSE(tree.search("HELL"));
    ASSERT_FALSE(tree.search("WORL"));
    ASSERT_FALSE(tree.search("HELLOWORLD"));
}

TEST(RadixTree, WordScore) {
    Radix tree;
    ASSERT_EQ(tree.get_word_score("HELLO"), 8);
    ASSERT_EQ(tree.get_word_score("WORLD"), 9);
    ASSERT_EQ(tree.get_word_score(""), 0);
}

TEST(RadixTree, FindWords) {
    Radix tree;
    tree.insert("CAT");
    tree.insert("CAR");
    tree.insert("CART");
    tree.insert("A");
    tree.insert("AT");

    std::vector<std::string> words = tree.find_words("ATCR");
    std::sort(words.begin(), words.end());
    
    std::vector<std::string> expected_words = {"A", "AT", "CAR", "CART", "CAT"};
    std::sort(expected_words.begin(), expected_words.end());

    ASSERT_EQ(words, expected_words);
}

TEST(RadixTree, PrefixesAndSplits) {
    Radix tree;
    tree.insert("CAR");
    tree.insert("CART");
    tree.insert("CAT");
    tree.insert("CATER");
    tree.insert("DOG");

    ASSERT_TRUE(tree.search("CAR"));
    ASSERT_TRUE(tree.search("CART"));
    ASSERT_TRUE(tree.search("CAT"));
    ASSERT_TRUE(tree.search("CATER"));
    ASSERT_TRUE(tree.search("DOG"));

    ASSERT_FALSE(tree.search("CA")); // Prefix but not a word
    ASSERT_FALSE(tree.search("CATE")); // Prefix but not a word
    ASSERT_FALSE(tree.search("DO")); // Prefix but not a word
    ASSERT_FALSE(tree.search("DRY")); // Not in tree
}

TEST(RadixTree, EdgeCases) {
    Radix tree;
    tree.insert("HELLO");
    tree.insert("WORLD");
    tree.insert("TEST");

    // Empty rack
    std::vector<std::string> words_empty_rack = tree.find_words("");
    ASSERT_TRUE(words_empty_rack.empty());

    // Rack with no matching words
    std::vector<std::string> words_no_match = tree.find_words("XYZ");
    ASSERT_TRUE(words_no_match.empty());

    // Rack with duplicate letters, forming existing words
    tree.insert("EEL");
    tree.insert("LE");
    std::vector<std::string> words_dup_rack = tree.find_words("EEL");
    std::sort(words_dup_rack.begin(), words_dup_rack.end());
    std::vector<std::string> expected_dup_rack = {"EEL", "LE"};
    std::sort(expected_dup_rack.begin(), expected_dup_rack.end());
    ASSERT_EQ(words_dup_rack, expected_dup_rack);

}

TEST(RadixTree, MixedCaseAndInvalidChars) {
    Radix tree;
    // Mixed case, should still score correctly due to toupper
    ASSERT_EQ(tree.get_word_score("hElLo"), 8);
    // Invalid characters, should be ignored (score 0 for those chars)
    ASSERT_EQ(tree.get_word_score("WORD!"), 8); // W=4, O=1, R=1, D=2, ! = 0
    ASSERT_EQ(tree.get_word_score("123ABC"), 7); // A=1, B=3, C=3, others 0
}

TEST(RadixTree, AnagramsFromDictionary) {
    Radix tree;
    // Importing dictionary file.
    std::ifstream file("scrabble_dictionary.txt");
    std::string word;
    while (file >> word) {
        tree.insert(word);
    }
    //Example four letter rack for a small output.
    std::vector<std::string> words = tree.find_words("ETTS");
    std::sort(words.begin(), words.end());

    std::vector<std::string> expected_words = {"ES", "ET", "SET", "SETT", "STET", "TEST", "TET", "TETS"};
    std::sort(expected_words.begin(), expected_words.end());

    ASSERT_EQ(words, expected_words);

    std::map<std::string, int> expected_scores;
    expected_scores["ES"] = 2;
    expected_scores["ET"] = 2;
    expected_scores["SET"] = 3;
    expected_scores["SETT"] = 4;
    expected_scores["STET"] = 4;
    expected_scores["TEST"] = 4;
    expected_scores["TET"] = 3;
    expected_scores["TETS"] = 4;

    for(const auto& w : words) {
        EXPECT_EQ(tree.get_word_score(w), expected_scores[w]);
    }
}
