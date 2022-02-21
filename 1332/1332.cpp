#include <string>

/**
 * 删除仅含 a 和 b 的串的回文子序列（不一定连续），直到原串变成空串
 * 其实是脑筋急转弯题目，因为要么删一次，要么删两次就行了
 */
class Solution {
public:
    int removePalindromeSub(std::string s) {
        int n = s.length();
        for (int i = 0; i < n / 2; i++) {
            if (s[i] != s[n - i - 1]) {
                return 2;
            }
        }
        return 1;
    }
};