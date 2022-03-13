#include <unordered_map>
#include <string>
using std::string;

/**
 * 微软笔试题，困难滑动窗口
 * 
 * 贪心思路：
 * 0. l = 0, r = 0
 * 1. r++ 直到包含了所有元素
 * 2. l++ 直到恰好包含了所有元素，更新答案
 * 3. l++. 然后 goto 1. 直到 r >= n
 */
class Solution {
    std::pair<int, int> minDis(std::pair<int, int> a, std::pair<int, int> b) {
        const int disA = a.second - a.first;
        const int disB = b.second - b.first;
        return disA < disB ? a : b;
    }
public:
    string minWindow(string s, string t) {
        const int n = s.length();
        const int m = t.length();

        std::unordered_map<char, int> targets;
        for (const char c : t) {
            targets[c]++;
        }
        std::unordered_map<char, int> curChars;
        int curCharCnt = 0;
        std::pair<int, int> ans = {0, n};

        int l = 0, r = 0;
        for (; r < n; r++) {
            if (curChars[s[r]] < targets[s[r]]) {
                curCharCnt++;
            }
            curChars[s[r]]++;

            if (curCharCnt == m) {
                for (; ; l++) {
                    if (curChars[s[l]] == targets[s[l]]) {
                        break;
                    }
                    curChars[s[l]]--;
                }
                ans = minDis(ans, {l, r});

                curChars[s[l]]--;
                curCharCnt--;
                l++;
            }

        }
        if (ans.second == n) {
            return "";
        }
        return s.substr(ans.first, ans.second - ans.first + 1);
    }
};