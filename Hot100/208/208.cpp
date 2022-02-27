#include <string>
using std::string;

/**
 * Trie 字典树的实现
 */
class Trie {
    static const int CHAR_NUM = 26;

    bool isEnd = false;
    Trie *next[CHAR_NUM] = {nullptr};

public:
    Trie() {
    }
    
    void insert(string word) {
        Trie *node = this;
        for (const char c : word) {
            const int charIndex = c - 'a';
            if (node->next[charIndex] == nullptr) {
                node->next[charIndex] = new Trie();
            }
            node = node->next[charIndex];
        }
        node->isEnd = true;
    }
    
    bool search(string word) {
        Trie *node = this;
        for (const char c : word) {
            const int charIndex = c - 'a';
            node = node->next[charIndex];
            if (node == nullptr) {
                return false;
            }
        }
        return node->isEnd;
    }
    
    bool startsWith(string prefix) {
        Trie *node = this;
        for (const char c : prefix) {
            const int charIndex = c - 'a';
            node = node->next[charIndex]; 
            if (node == nullptr) {
                return false;
            }
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */