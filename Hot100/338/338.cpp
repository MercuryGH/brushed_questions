#include <vector>

/**
 * 对于 0 <= i <= n 中的每个 i ，计算其二进制表示中 1 的个数 ，返回一个长度为 n + 1 的数组 ans 作为答案。
 * 暴力做法对每个数都进行二进制位计数，时间复杂度为 O(n log n)
 * 
 * 动态规划法能把时间复杂度降到 O(n). 详见 dp.md
 */
class Solution {
public:
    std::vector<int> countBits(int n) {
        std::vector<int> dp(n + 1);
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            if (i % 2 == 1) {
                dp[i] = dp[i - 1] + 1;
            } else {
                dp[i] = dp[i / 2];
            }
        }
        return dp;
    }
};