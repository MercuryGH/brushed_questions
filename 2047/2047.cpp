#include <string>
#include <regex>
#include <sstream>

class Solution {
public:
    int countValidWords(std::string sentence) {
        std::regex wordRegex = std::regex("[a-z]*([a-z]-[a-z])?[a-z]*[!.,]?");

        int res = 0;
        std::string word;
        for (std::istringstream iss(sentence); iss >> word; ) { // 相当于 split() 后的结果一个一个赋给 word
            res += std::regex_match(word, wordRegex);
        }
        return res;
    }
};