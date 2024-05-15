
#include <iostream>
#include <vector>
#include <memory>
#include <queue>

using namespace std;

class TrieNode {
public:
    vector<unique_ptr<TrieNode>> children;
    bool isEndOfWord;

    TrieNode() : children(27), isEndOfWord(false) {}

    int getIndex(char c) {
        if (c == '\'') {
            return 26;
        }
        if (isupper(c)) {
            c = tolower(c);
        }
        return c - 'a';
    }
};

class Trie {
public:
    unique_ptr<TrieNode> root;
    int wordCount;

    Trie() : root(make_unique<TrieNode>()), wordCount(0) {}

    void insert(const string& word) {
        TrieNode* current = root.get();
        for (char c : word) {
            int index = current->getIndex(c);
            if (!current->children[index]) {
                current->children[index] = make_unique<TrieNode>();
            }
            current = current->children[index].get();
        }
        if (!current->isEndOfWord) {
            current->isEndOfWord = true;
            wordCount++;
        }
    }

    int getCount() {
        return wordCount;
    }

    bool search(const string& word) {
        TrieNode* current = root.get();
        for (char c : word) {
            int index = current->getIndex(c);
            if (!current->children[index]) {
                return false;
            }
            current = current->children[index].get();
        }
        return current && current->isEndOfWord;
    }

    vector<string> suggestCorrections(const string& word) {
        vector<string> suggestions;
        // Insertion
        for (size_t i = 0; i <= word.size(); i++) {
            for (char c = 'a'; c <= 'z'; c++) {
                string newWord = word;
                newWord.insert(i, 1, c);
                if (search(newWord)) {
                    suggestions.push_back(newWord);
                }
            }
        }
        // Replacement
        for (size_t i = 0; i < word.size(); i++) {
            string temp = word;
            for (char c = 'a'; c <= 'z'; c++) {
                temp[i] = c;
                if (c != word[i] && search(temp)) {
                    suggestions.push_back(temp);
                }
            }
        }
        // Deletion
        for (size_t i = 0; i < word.size(); i++) {
            string reducedWord = word.substr(0, i) + word.substr(i + 1);
            if (search(reducedWord)) {
                suggestions.push_back(reducedWord);
            }
        }
        // Swap adjacent characters
        for (size_t i = 0; i < word.size() - 1; i++) {
            string swappedWord = word;
            swap(swappedWord[i], swappedWord[i + 1]);
            if (search(swappedWord)) {
                suggestions.push_back(swappedWord);
            }
        }
        return suggestions;
    }
};
