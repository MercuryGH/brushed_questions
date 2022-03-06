#include <vector>
#include <algorithm>
using std::vector;

/**
 * 传纸条（两趟）
 * 棋盘DP经典
 */
class Solution
{
    static constexpr int MAXN = 55;
    static constexpr int INF = 114514;

    // 初始化所有格点为不可达状态
    int dp[MAXN][MAXN][MAXN][MAXN]; // 这种初始化只是把第一个元素赋值为-INF，其他元素仍为0 ！！
    // int dp[MAXN][MAXN][MAXN][MAXN] = {-INF}; // 这种初始化只是把第一个元素赋值为-INF，其他元素仍为0 ！！

    int max4Adj(int i, int j, int k, int l)
    {
        int dp1, dp2, dp3, dp4;
        dp1 = dp2 = dp3 = dp4 = -INF;
        if (i > 0)
        {
            if (k > 0)
            {
                dp1 = dp[i - 1][j][k - 1][l];
            }
            if (l > 0)
            {
                dp2 = dp[i - 1][j][k][l - 1];
            }
        }
        if (j > 0)
        {
            if (k > 0)
            {
                dp3 = dp[i][j - 1][k - 1][l];
            }
            if (l > 0)
            {
                dp4 = dp[i][j - 1][k][l - 1];
            }
        }
        return std::max(dp1, std::max(dp2, std::max(dp3, dp4)));
    }

    void setInf(vector<vector<int>> &grid, int n, int m) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == -1) {
                    grid[i][j] = -INF; // 更彻底一点
                }
            }
        }

        // 初始化所有格点为不可达状态
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                for (int k = 0; k < n; k++)
                    for (int l = 0; l < m; l++)
                        dp[i][j][k][l] = -INF;
    }

public:
    int cherryPickup(vector<vector<int>> &grid)
    {
        const int n = grid.size();
        const int m = grid[0].size();
        setInf(grid, n, m);

        dp[0][0][0][0] = grid[0][0]; // 必须
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                for (int k = 0; k < n; k++)
                {
                    for (int l = 0; l < m; l++)
                    {
                        int ans = max4Adj(i, j, k, l);
                        if (ans == -INF) { // 如果不可达，直接离开
                            continue;
                        }
                        if (i == k && j == l)
                        {
                            ans += grid[i][j];
                        }
                        else
                        {
                            ans += grid[i][j] + grid[k][l];
                        }
                        dp[i][j][k][l] = ans;
                    }
                }
            }
        }
        return dp[n - 1][m - 1][n - 1][m - 1] >= 0 ? dp[n - 1][m - 1][n - 1][m - 1] : 0;
    }
};