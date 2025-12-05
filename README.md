# Radix Tree Anagram Solver

> A C++ implementation of a Radix Tree for finding and scoring Scrabble anagrams.

## Introduction
This project implements a Radix Tree, a space-optimized data structure for storing and searching for strings. The Radix Tree is used here to create an anagram solver for Word games like Scrabble. Given a "rack" of letters, the program efficiently finds all possible words from a dictionary that can be formed and sorts them by their Scrabble score. A Radix Tree is interesting because it compresses the path of nodes with single children, which makes it more memory-efficient than a standard Trie, especially for large dictionaries.

## Features
- **Radix Tree Data Structure:** Core implementation of a Radix Tree with insert and search operations.
- **Anagram Finder:** Finds all words that can be formed from a given set of letters (a "rack").
- **Scrabble Scoring:** Calculates the Scrabble score for each found word.
- **Sorted Output:** Displays the found words sorted in descending order of their scores.
- **Dictionary Loading:** Loads a dictionary of words from a file to populate the Radix Tree.

## How the Data Structure Works
A Radix Tree is a tree-like data structure where each node represents a string. Unlike a standard Trie where each edge represents a single character, the edges in a Radix Tree can represent a sequence of characters. This is achieved by merging nodes that do not have siblings, which significantly reduces the tree's depth and memory usage.

When inserting a word, we traverse the tree, following edges that match the prefix of the word. If the word diverges from an existing path, a new branch is created. If a word is a prefix of an existing word, or vice versa, nodes are split to accommodate both.

To find anagrams from a rack of letters, the algorithm performs a recursive traversal of the tree. At each node, it checks if the letters in the current rack are sufficient to traverse to a child node. If so, it recursively continues the search down that path, updating the available letters. When it reaches a node that marks the end of a word, that word is added to the results.

### Time and Space Complexity
Where `k` is the length of the string being processed.

| Operation | Average Case | Worst Case |
|-----------|--------------|------------|
| Insert    | O(k)         | O(k)       |
| Search    | O(k)         | O(k)       |

The complexity of finding all anagrams depends on the number of letters in the rack and the number of valid words in the dictionary.

## File Structure
```
/app
├── main.cpp                            # Main function file
/code
├── AnagramSolver.h                     # Header file for the Radix class
├── AnagramSolver.cpp                   # Implementation of the Radix class
├── scrabble_dictionary.txt             # Dictionary file used by the program
/build
/tests
├── test.cpp                            # Test file for unit testing.
└── CMakeLists.txt                      # CMake file for unit testing.
└── README.md                           # This is the README file
```

## Installation / Setup
To compile and run this project, you will need a C++ compiler (like g++).

1.  **Clone the repository or download the files.**

2.  **Open a terminal and navigate to the project directory.**

3.  **Compile the source code:**
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

4.  **Run the program:**
    ```bash
    ./anagram_solver "TEST"
    ```

5.  **Run the unit tests:**
    ```bash
    ./run_tests
    ```

## Usage
When you run the program, it will take in a char argument (a string of letters called the rack (e.g., "TEST"). The program will then load the dictionary from `scrabble_dictionary.txt` and populate the Radix tree. The program will output all the words that can be formed from those letters, along with their Scrabble scores, sorted from highest to lowest score. No blank tiles\spaces can be included in this program. Extra letters, such as those already on the board, can be included to find words that will work with current game play.

**Example Output:**

```
********************************************
|                                          |
|              ANAGRAM SOLVER              |
|                                          |
********************************************
--------------------------------------------
 Words that can be formed from the letters: 
                  TEST
--------------------------------------------
SETT (Score: 4)
STET (Score: 4)
TEST (Score: 4)
TETS (Score: 4)
SET (Score: 3)
TET (Score: 3)
ES (Score: 2)
ET (Score: 2)
--------------------------------------------
```

## Application Demo
The demo application showcases the power of the Radix Tree for solving a real-world problem like finding Scrabble anagrams. By pre-processing the dictionary into a Radix Tree, the search for valid words from a given rack of letters is significantly optimized. The application also demonstrates how additional features, like scoring, can be built on top of the core data structure.

## Testing
The `main` function in `main.cpp` serves as the primary test driver for this project. You can test the functionality by:
-   Running the program with various letter racks to verify that the correct anagrams are found.
-   Checking the scores of the output words to ensure the scoring is correct.
-   Modifying the `scrabble_dictionary.txt` file (e.g., adding or removing words) to see how the program's output changes.
The `gtests` in test.cpp serves as unit testing to verify that each function is working correctly. These 7 unit tests are included:
-  InsertAndSearch: Inserts words into the Radix tree and then searches to verify what words exist.
-  WordScore: Verifies that the score given to a word is correct.
-  FindWords: Inserts words into the Radix tree and then looks for anagrams that can be formed with the letters that have been used in the inserted words.
-  PrefixesAndSplits: Inserts words into the Radix tree. Checks for splits/prefixes/complete words.
-  EdgeCases: Inserts words into the Radix tree. Checks output for an empty rack, no matching words and rack with duplicate letters. 
-  MixedCaseAndInvalidChars: All letters give the proper score, their case does not matter. Invalid characters give no points and are not included in any output anagrams.
-  AnagramsFromDictionary: loads the `scrabble_dictionary.txt` file. A sample rack is provided. The program runs as if it was given a user input rack and checks for all possible anagrams and that their scores are correct.


## References
Wikipedia. Radix tree. https://en.wikipedia.org/wiki/Radix_tree
Wikipedia. Backtracking. https://en.wikipedia.org/wiki/Backtracking
Wikipedia. Scrabble. https://en.wikipedia.org/wiki/Scrabble
Wikipedia. Scrabble Letter Distributions. https://en.wikipedia.org/wiki/Scrabble_letter_distributions
University of San Fransisco. Radix Tree Visualization. https://www.cs.usfca.edu/~galles/visualization/RadixTree.html
ZyBooks Computer Science 2: Data Structures, Chapter 7 Trees, Section 7.12 Tries
Introduction to Algorithms, Cormen, Thomas H., 2009, Chapter 12 Binary Search Trees, Section 12-2 Radix trees, pages 304-307
Theory of Coding. Compressed Trie Tree. https://theoryofcoding.com/index.php/2016/11/15/compressed-trie-tree/
Free Scrabble Dictionary. Dictionary text file download. https://www.freescrabbledictionary.com/twl06/

## Future Improvements
Implement functionality to handle blank tiles (wildcards) in the letter rack. A blank tile could substitute for any letter, but would contribute zero points to the word's score. This would involve modifying the `find_words_helper` function to account for a blank tile by trying all possible letters when a blank is encountered, effectively branching the search for each letter of the alphabet. The user input mechanism would also need to be updated to allow for a special character (e.g., '?') to represent a blank tile in the rack. The `get_word_score` function would also need to be updated to make sure that the score of the wildcard character would be 0.

