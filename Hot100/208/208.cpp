#include <string>
using std::string;

/**
 * Trie 字典树的实现
 */
class Trie
{
    static constexpr int CHAR_NUM = 26;

    bool isEnd = false;
    Trie *next[CHAR_NUM] = {nullptr}; // 需要显式初始化为 {nullptr}。注意在nullptr语境下，next数组的所有元素均为 NULL

public:
    Trie()
    {
    }

    void insert(string word)
    {
        Trie *node = this;
        for (const char c : word)
        {
            const int charIndex = c - 'a';
            if (node->next[charIndex] == nullptr)
            {
                node->next[charIndex] = new Trie();
            }
            node = node->next[charIndex];
        }
        node->isEnd = true;
    }

    bool search(string word)
    {
        Trie *node = this;
        for (const char c : word)
        {
            const int charIndex = c - 'a';
            if (node->next[charIndex] == nullptr)
            {
                return false;
            }
            node = node->next[charIndex];
        }
        return node->isEnd;
    }

    bool startsWith(string prefix)
    {
        Trie *node = this;
        for (const char c : prefix)
        {
            const int charIndex = c - 'a';
            if (node->next[charIndex] == nullptr)
            {
                return false;
            }
            node = node->next[charIndex];
        }
        return true;
    }
};
