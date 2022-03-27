#include <vector>
#include <algorithm>
#include <numeric> // std::accumulate
using std::vector;

/**
 * 分割等和子集：给定序列，输出是否可以将该序列分成两个子集，且这两个子集的各元素之和相等。
 * 转化为：输出是否可以枚举若干序列中的元素，使得这些元素之和 恰好为 整个序列的元素之和的一半
 * 
 * 01背包变体
 */
class Solution
{
public:
    bool canPartition(vector<int> &nums)
    {
        const int n = nums.size();
        const int sum = std::accumulate(nums.begin(), nums.end(), 0);
        if (n < 2 || sum % 2 == 1) {
            return false;
        }

        const int target = sum / 2;
        const int maxElement = *std::max_element(nums.begin(), nums.end());
        if (maxElement > target) {
            return false;
        }

        vector<vector<bool>> dp(n, vector<bool>(target + 1, false)); // dp[n - 1][target]
        for (int i = 0; i < n; i++) {
            dp[i][0] = true;
        }
        dp[0][nums[0]] = true;
        for (int i = 1; i < n; i++) {
            for (int j = 1; j <= target; j++) {
                if (j >= nums[i]) {
                    dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i]];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[n - 1][target];
    }
};
