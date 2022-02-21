#include <algorithm>
#include <string>
#include <vector>

/**
 * 最长回文子串
 * 
 * 标准答案：DP O(n^2)、Manacher 算法 O(n)
 */
class Solution {
public:
    std::string longestPalindrome(std::string s) {
        const int n = s.size();
        if (n < 2) {
            return s;
        }

        int maxLen = 1;
        int beginIndex = 0;

        // 注意：dp数组不使用 i > j 的部分
        std::vector<std::vector<bool>> dp(n, std::vector<bool>(n));  
        for (int i = 0; i < n; i++) {
            dp[i][i] = true;
        }

        for (int len = 2; len <= n; len++) {
            for (int i = 0; i < n; i++) {
                int j = len + i - 1;
                if (j >= n) {
                    break;
                }
                if (j - i == 1) {  // 由于dp[i + 1][i] 属于 i > j 的部分，所以要特判
                    dp[i][j] = s[i] == s[j];  
                } else {
                    dp[i][j] = s[i] == s[j] && dp[i + 1][j - 1];
                }

                if (dp[i][j] == true && len > maxLen) {
                    maxLen = len;
                    beginIndex = i;
                }
            }
        }
        return s.substr(beginIndex, maxLen);
    }
};