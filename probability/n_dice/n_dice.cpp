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
using std::vector, std::string;

class Solution
{
public:
    vector<double> dicesProbability(int n)
    {
        vector<vector<double>> dp(n + 1, vector<double>(6 * n + 1, 0));
        for (int i = 1; i <= 6; i++) {
            dp[1][i] = (double)1 / 6;
        }

        for (int i = 2; i <= n; i++)
        {
            for (int j = i; j <= 6 * i; j++)
            {
                double acc = 0;
                for (int k = 1; k <= 6; k++)
                {
                    if (j - k >= i - 1) {
                        acc += dp[i - 1][j - k];
                    }
                }
                dp[i][j] = acc / 6;
            }
        }
        
        vector<double> ans;
        for (int i = n; i <= 6 * n; i++) {
            ans.push_back(dp[n][i]);
        }
        return ans;
    }
};