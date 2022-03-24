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

/*
DP 写挂了，居然过不了一个点，呵呵
*/
class Solution
{
    int n;
    static constexpr int INF = 0x3f3f3f3f;
    bool outOfBound(int x, int y)
    {
        return x < 0 || x >= n || y < 0 || y >= n;
    }

public:
    int minimumMoves(vector<vector<int>> &grid)
    {
        n = grid.size();

        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(n + 1, vector<int>(2, INF)));
        dp[0][0][0] = 0;
        if (grid[1][0] == 0 && grid[1][1] == 0)
        {
            dp[0][0][1] = 1;
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < 2; k++)
                {
                    int tmp1, tmp2, tmp3, tmp4;
                    tmp1 = tmp2 = tmp3 = tmp4 = INF;
                    const bool upBlockValid = outOfBound(i - 1, j) == false && grid[i - 1][j] == 0;
                    const bool leftBlockValid = outOfBound(i, j - 1) == false && grid[i][j - 1] == 0;
                    const bool rightBlockValid = outOfBound(i, j + 1) == false && grid[i][j + 1] == 0;
                    const bool downBlockValid = outOfBound(i + 1, j) == false && grid[i + 1][j] == 0;
                    const bool rightDownBlockValid = outOfBound(i + 1, j + 1) == false && grid[i + 1][j + 1] == 0;
                    const bool canTransfer = k == 0 && rightBlockValid || k == 1 && downBlockValid;
                    const bool canSecondTransfer = k == 1 && rightBlockValid || k == 0 && downBlockValid;
                    if (upBlockValid && canTransfer) // 从上面转移
                    {
                        tmp1 = dp[i - 1][j][k];
                        if (rightDownBlockValid)
                        {
                            if (canSecondTransfer)
                            {
                                tmp3 = dp[i - 1][j][!k];
                            }
                        }
                    }
                    if (leftBlockValid && canTransfer) // 从左边转移
                    {
                        tmp2 = dp[i][j - 1][k];
                        if (rightBlockValid)
                        {
                            if (canSecondTransfer)
                            {
                                tmp4 = dp[i][j - 1][!k];
                            }
                        }
                    }
                    std::cout << i << " " << j << " " << k << "\n";
                    dp[i][j][k] = std::min(dp[i][j][k], std::min(std::min(tmp1, tmp2) + 1, std::min(tmp3, tmp4) + 2));
                }
            }
        }
        return dp[n - 1][n - 2][0] >= INF ? -1 : dp[n - 1][n - 2][0];
    }
};

