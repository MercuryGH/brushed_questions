#include <algorithm>
#include <ctime>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <list>
#include <string>
#include <sstream>
using std::vector, std::string;

/**
 * 反转字符串中的单词 III
 * 输入：s = "Let's take LeetCode contest"
   输出："s'teL ekat edoCteeL tsetnoc"

 * 其实C++根本不需要 ostringstream，直接用可变的 string 就可以了
 */
class Solution {
public:
    string reverseWords(string s) {
        const int len = s.length();
        std::istringstream sStream(s); 

        vector<string> words;
        while (true) {
            string word;
            sStream >> word;
            if (word.length() == 0) {
                break;
            }
            words.emplace_back(word);
        }

        const int n = words.size();
        for (string &word : words) {
            std::reverse(word.begin(), word.end());
        }

        std::ostringstream ans;
        for (int i = 0; i < n - 1; i++) {
            ans << words[i] << " ";
        }
        ans << words[n - 1];

        return ans.str();
    }
};