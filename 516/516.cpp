#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
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
    int longestPalindromeSubseq(string s)
    {
        const int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }

        for (int len = 1; len <= n; len++) {
            for (int i = 0; i < n; i++) {
                int j = i + len - 1;
                if (j >= n) {
                    continue;
                }

                if (j - i >= 2 && s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                } else if (j - i >= 1 && s[i] != s[j]) {
                    dp[i][j] = std::max(dp[i + 1][j], dp[i][j - 1]);
                } else if (j - i == 1 && s[i] == s[j]) {
                    dp[i][j] = 2;
                } 
            }
        }
        return dp[0][n - 1];
    }
};