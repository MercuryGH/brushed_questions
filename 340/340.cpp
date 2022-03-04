#include <vector>
#include <string>
#include <unordered_map>
using std::string;

/**
 * 至多包含 K 个不同字符的最长子串
 * 区间DP解毫无时间复杂度优势，因此用滑动窗口
 */
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        if (k == 0) {
            return 0;
        }

        const int n = s.length();
        std::unordered_map<char, int> hash;
        int l = 0;
        int r = 0;
        int curDistinctCharInWindow = 0;
        for (; ; r++) {
            const char curChar = s[r];
            if (hash.find(curChar) == hash.end()) {
                curDistinctCharInWindow++;
            }
            hash[curChar]++;
            if (curDistinctCharInWindow == k || r == n - 1) {
                break;
            }
        }

        int ans = r - l + 1;
        while (true) {
            r++;
            if (r >= n) {
                break;
            }
            const char newChar = s[r];
            if (hash.find(newChar) == hash.end() || hash[newChar] == 0) { // 超出 k 个
                while (true) {
                    const char oldChar = s[l];
                    hash[oldChar]--;
                    l++;
                    if (hash[oldChar] == 0) {
                        break;
                    }
                }
            } 
            hash[newChar]++;
            ans = std::max(ans, r - l + 1);
        }
        return ans;
    }
};