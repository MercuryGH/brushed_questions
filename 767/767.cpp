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
 * 重构字符串
 * 给定一个字符串 s ，检查是否能重新排布其中的字母，使得两相邻的字符不同。
 * 输出 s 的任一可行重构
 * 
 * 思路：贪心，每次从堆中 pop max 和 次max，然后更新该字符出现的频率。
 */
class Solution {
    struct CharFreq {
        char c;
        int freq;
        CharFreq(char c, int freq): c(c), freq(freq) {}
    };
public:
    string reorganizeString(string s) {
        const auto cmp = [](const CharFreq charFreq1, const CharFreq charFreq2) {
            return charFreq1.freq < charFreq2.freq; // 注意写成 <= 会错！！
            // <= 可能会改变已经排好了的位置的相对次序，而 < 不会。所以以后在写 cmp 时，写 < 更好
        };
        std::priority_queue<
            CharFreq, 
            vector<CharFreq>,
            decltype(cmp)
        > q(cmp);  // 最大堆

        std::unordered_map<char, int> freqHash;
        for (const char c : s) {
            freqHash[c]++;
        }
        for (char c = 'a'; c <= 'z'; c++) {
            const int cFreq = freqHash[c];
            if (cFreq > 0)
                q.emplace(c, cFreq);
        }

        string ans;
        while (true) {
            if (q.size() <= 1) {
                break;
            }
            CharFreq maxCharFreq = q.top();
            q.pop();
            CharFreq subMaxCharFreq = q.top();
            q.pop();

            // ans += maxCharFreq.c + subMaxCharFreq.c; // 错了，注意加号重载！！
            ans += maxCharFreq.c;
            ans += subMaxCharFreq.c;
            
            maxCharFreq.freq--;
            subMaxCharFreq.freq--;
            if (maxCharFreq.freq > 0) {
                q.push(maxCharFreq);
            }
            if (subMaxCharFreq.freq > 0) {
                q.push(subMaxCharFreq);
            }
        }
        if (q.size() == 1) {
            CharFreq remainedCharFreq = q.top();
            if (remainedCharFreq.freq > 1) {
                return "";
            }
            ans += remainedCharFreq.c;
        }
        return ans;
    }
};
