#include <vector>

class Solution
{
public:
    int minSteps(int n)
    {
        std::vector<int> dp(n + 1, INT_MAX);
        dp[1] = 0;

        for (int i = 2; i <= n; i++) {
            for (int j = 2; j <= i; j++) {
                if (i % j == 0) {
                    dp[i] = std::min(dp[i / j] + j, dp[i]);
                }
            }
        }

        return dp[n];
    }
};
