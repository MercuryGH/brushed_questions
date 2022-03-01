#include <vector>
#include <numeric>
using std::vector;

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        const int n = nums.size();
        const int sum = std::accumulate(nums.begin(), nums.end(), 0);
        if (std::abs(target) > sum) {
            return 0;
        }

        vector<vector<int>> dp(n, vector<int>(2 * sum + 1, 0));
        dp[0][nums[0] + sum]++;
        dp[0][-nums[0] + sum]++;
        for (int i = 1; i < n; i++) {
            for (int j = -sum; j <= sum; j++) {
                if (j + nums[i] > sum) {
                    dp[i][j + sum] = dp[i - 1][j - nums[i] + sum];
                } else if (j - nums[i] < -sum) {
                    dp[i][j + sum] = dp[i - 1][j + nums[i] + sum];
                } else {
                    dp[i][j + sum] = dp[i - 1][j - nums[i] + sum] + dp[i - 1][j + nums[i] + sum];
                }
            }
        }
        return dp[n - 1][target + sum];
    }
};
