#include <algorithm>
#include <vector>
using std::vector;

class Solution
{
public:
    int maxCoins(vector<int> &nums)
    {
        const int n = nums.size();
        nums.insert(nums.begin(), 1);
        nums.push_back(1);

        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

        for (int len = 1; len <= n + 2; len++)
        {
            for (int i = 0; i <= n + 1; i++)
            {
                int j = i + len - 1;
                if (j > n + 1) {
                    continue;
                }

                if (j - i <= 1)
                {
                    dp[i][j] = 0;
                }
                else
                {
                    int maxDp = 0;
                    for (int k = i + 1; k <= j - 1; k++)
                    {
                        maxDp = std::max(maxDp, dp[i][k] + (nums[i] * nums[k] * nums[j]) + dp[k][j]);
                    }
                    dp[i][j] = maxDp;
                }
            }
        }
        return dp[0][n + 1];
    }
};