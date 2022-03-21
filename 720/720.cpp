#include <algorithm>
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

class Solution
{
    struct Trie
    {
        static constexpr int CHAR_NUM = 26;

        bool isEnd = false;
        Trie *children[CHAR_NUM] = {nullptr};

        Trie() {}

        void insert(string word)
        {
            Trie *node = this;
            for (const char c : word)
            {
                const int charIndex = c - 'a';
                if (node->children[charIndex] == nullptr)
                {
                    node->children[charIndex] = new Trie();
                }
                node = node->children[charIndex];
            }
            node->isEnd = true;
        }

        bool search(string word)
        {
            Trie *node = this;
            for (const char c : word)
            {
                const int charIndex = c - 'a';
                if (node->children[charIndex] == nullptr)
                {
                    return false;
                }
                node = node->children[charIndex];
            }
            return node->isEnd;
        }

        bool searchWithAllEnd(string word)
        {
            Trie *node = this;
            for (const char c : word)
            {
                const int charIndex = c - 'a';
                if (node->children[charIndex] == nullptr || node->children[charIndex]->isEnd == false)
                {
                    return false;
                }
                node = node->children[charIndex];
            }
            return node->isEnd;
        }
    };

public:
    string longestWord(vector<string> &words)
    {
        Trie *trie = new Trie();
        for (const auto &word : words)
        {
            trie->insert(word);
        }

        string ans;
        for (const auto &word : words)
        {
            if (trie->searchWithAllEnd(word))
            {
                if (word.length() > ans.length() || (word.length() == ans.length() && word < ans)) {
                    ans = word;
                }
            }
        }
        return ans;
    }
};