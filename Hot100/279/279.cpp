#include <vector>
#include <algorithm>
using std::vector;

/**
 * 给你一个整数n ，返回和为 n 的完全平方数的最少数量。
 */
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, 114514);
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j * j <= i; j++) {
                dp[i] = std::min(dp[i], dp[i - j * j] + 1);
            }
        }
        return dp[n];
    }
};