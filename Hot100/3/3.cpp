#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::vector, std::string, std::pair;

/**
 * 找出无重复字符的最长子串的长度
 * 动态规划写不出来
 *
 * 标准答案：滑动窗口，时间复杂度仅 O(n)
 * 拓展题目（推广）：至多包含 k 个不同字符的最长子串 (Leetcode 340)，还是滑动窗口
 */
class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        std::unordered_set<char> lookup;
        int ans = 0;

        int window_left = 0;
        int window_right = 0;
        for (int i = 0; i < s.length(); i++) {
            window_right = i;
            if (lookup.find(s.at(i)) != lookup.end()) { // find something
                while (true) {
                    lookup.erase(s.at(window_left));
                    window_left++;
                    if (lookup.find(s.at(i)) == lookup.end()) {
                        break;
                    }
                }
            }
            ans = std::max(ans, window_right - window_left + 1);

            lookup.insert(s.at(i));
        }

        return ans;
    }
};
