#include <vector>
#include <algorithm>
using std::vector;

class Solution
{
public:
    int maximalSquare(vector<vector<char>> &matrix)
    {
        const int n = matrix.size();
        const int m = matrix[0].size();
        vector<vector<int>> dp(n, vector<int>(m));

        int ans = -1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 || j == 0) {
                    dp[i][j] = matrix[i][j] - '0';
                } else if (matrix[i][j] == '0') {
                    dp[i][j] = 0;
                } else {
                    dp[i][j] = std::min(std::min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]) + 1;
                }
                ans = std::max(ans, dp[i][j]);
            }
        }
        return ans * ans;
    }
};

