#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::vector, std::string;

class WordsFrequency
{
    struct TrieNode {
        static constexpr int CHAR_NUM = 26;

        TrieNode *children[CHAR_NUM] = {nullptr};
        int cnt = 0;
        bool isEnd = false;

        TrieNode() {}

        void insert(string s) {
            TrieNode *cur = this;
            for (const char c : s) {
                const int charIndex = c - 'a';
                if (cur->children[charIndex] == nullptr) {
                    cur->children[charIndex] = new TrieNode();
                }
                cur = cur->children[charIndex];
            }
            cur->cnt++;
            cur->isEnd = true;
        }
        
        int getCnt(string s) {
            TrieNode *cur = this;
            for (const char c : s) {
                const int charIndex = c - 'a';
                if (cur->children[charIndex] == nullptr) {
                    return 0;
                }
                cur = cur->children[charIndex];
            }
            return cur->cnt;
        }
    };

    TrieNode *root;

public:
    WordsFrequency(vector<string> &book)
    {
        root = new TrieNode();
        for (const string word : book) {
            root->insert(word);
        }
    }

    int get(string word)
    {
        return root->getCnt(word);
    }
};