#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

/**
 * 等价于找出在两个句子中一共只出现一次的单词。·
 * 所以只需要一个哈希表就能解决此题
 */
class Solution {
public:
    std::vector<std::string> uncommonFromSentences(std::string s1, std::string s2) {
        std::unordered_map<std::string, int> wordFreq;
        const auto insert = [&](const std::string &s) {
            std::string word;
            for (std::istringstream iss(s); iss >> word; ) {
                wordFreq[std::move(word)]++; 
                // std::move() 内的变量 word 表明亡值语义：
                /*
                    1. word 不再需要在当前函数中使用
                    2. 如果 wordFreq[] 重载了右值版本的[]运算符，则其可以利用移动语义节省开销
                */
                // wordFreq[word]++; 也可以，但会比右值版本慢一些
            }
        };  // 用 lambda 表达式完成构建哈希表语义
        insert(s1);
        insert(s2);

        std::vector<std::string> ans;
        for (const auto &[word, freq] : wordFreq) {
            if (freq == 1) {
                ans.push_back(word);
            }
        }
        return ans;
    }
};