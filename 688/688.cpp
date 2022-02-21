#include <vector>
using std::vector;

/**
 * 马的初始位置在 (row, column)
 * 在 n * n 的棋盘上，随机移动 k 步，计算其仍留在棋盘上的概率
 */
class Solution
{
    const int dirs[8][2] = {{-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}};

    bool isOutOfBound(int n, int x, int y) {
        return x < 0 || x >= n || y < 0 || y >= n;
    }

public:
    double knightProbability(int n, int k, int row, int column)
    {
        vector<vector<vector<double>>> dp(n, vector<vector<double>>(n, vector<double>(k + 1)));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j][0] = 1;
            }
        }

        for (int step = 1; step <= k; step++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    dp[i][j][step] = 0;
                    for (const auto &dir : dirs) {
                        const int nx = i + dir[0];
                        const int ny = j + dir[1];
                        if (isOutOfBound(n, nx, ny)) {
                            continue;
                        }
                        dp[i][j][step] += dp[nx][ny][step - 1] / 8;
                    }
                }
            }
        }
        return dp[row][column][k];
    }
};