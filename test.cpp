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

// 注意本题是“出界”，不是“仍留在棋盘上”。而且一旦出界，就不能再移动了
// 记 dp[P][k] 为当前位于点 P 时，**恰好**走 k 步所能出界的方案数
// 为什么这个“恰好”也是“至少”？这是因为对于所有出界的点P，都有f[P][any] = 1，故f[P][k - 1] = 1
class Solution {
    static constexpr int MOD = 1e9 + 7;

    int dirs[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    int m, n;

    bool outOfBound(int x, int y) {
        return x < 0 || x >= m || y < 0 || y >= n;
    }

public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        this->m = m;
        this->n = n;
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(maxMove + 1, 0)));
        // dp[IN][0] = 0;

        for (int k = 1; k <= maxMove; k++) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    for (const auto &dir : dirs) {
                        const int nx = i + dir[0];
                        const int ny = j + dir[1];
                        if (outOfBound(nx, ny) == false) {
                            dp[i][j][k] += dp[nx][ny][k - 1];
                        } else {
                            // dp[OUT][ANY] = 1;
                            dp[i][j][k]++;
                        }
                        dp[i][j][k] %= MOD;
                    }
                    // std::cout << dp[i][j][k] << "\n";
                }
            }
        }

        // int ans = 0;
        // for (int k = 1; k <= maxMove; k++) {
        //     std::cout << dp[startRow][startColumn][k] << "\n";
        //     ans += dp[startRow][startColumn][k];
        //     ans %= MOD;
        // }
        // return ans;
        return dp[startRow][startColumn][maxMove];
    }
};


int main()
{

    return 0;
}