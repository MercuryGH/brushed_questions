#include <algorithm>
#include <unordered_set>
#include <string>

/**
 * 找出无重复字符的最长子串的长度
 * 动态规划写不出来
 * 
 * 标准答案：滑动窗口，时间复杂度仅 O(n)
 * 拓展题目（推广）：至多包含 k 个不同字符的最长子串 (Leetcode 340)，还是滑动窗口
 */
class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        const int n = s.length();

        std::unordered_set<char> lookup;  // 滑动窗口内的含有的字符集合
        int maxLen = 0;
        int left = 0;
        for (int i = 0; i < n; i++) {  // i 用于枚举滑动窗口右端点
            const char cur = s[i];
            while (lookup.find(cur) != lookup.end()) {  // 在滑动窗口里找到了当前字符
                lookup.erase(s[left]);  // 滑动窗口左端点右移，直到找不到当前字符
                left++;
            }
            maxLen = std::max(maxLen, i - left + 1);  // 读一个字符，就更新答案
            lookup.insert(cur);  // 加入滑动窗口
        }
        return maxLen;
    }
};
