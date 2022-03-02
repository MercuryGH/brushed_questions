#include <algorithm>
#include <vector>
#include <iostream>
#include <stack>
using std::vector;

class Solution {
public:
    int integerBreak(int n) {
        vector<int> dp(n + 1, 0);
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= i - 1; j++) {
                dp[i] = std::max(dp[i], dp[i - j] * j);
                if (i != n) {
                    dp[i] = std::max(dp[i], i);
                }
            }
        }

        for (const auto num : dp) {
            std::cout << num << " ";
        }
        std::cout << "\n";


        return dp[n];
    }
};


int main()
{
    vector<int> nums = {73,74,75,71,69,72,76,73};
    int n = 2;
    Solution s;
    s.integerBreak(n);

    return 0;
}

