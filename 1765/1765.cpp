// 多源 BFS 模板
#include <vector>
#include <queue>

class Solution
{
    static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
public:
    std::vector<std::vector<int>> highestPeak(std::vector<std::vector<int>> &isWater)
    {
        int m = isWater.size();
        int n = isWater[0].size();

        // 初始化一个 m * n 的二维数组，初始化元素为 -1
        // -1 表示该格子尚未被访问过
        std::vector<std::vector<int>> ans(m, std::vector<int>(n, -1));  
        std::queue<std::pair<int, int>> q;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (isWater[i][j]) {
                    ans[i][j] = 0;
                    q.emplace(i, j);  // 水域入队
                }
            }
        }

        while (q.empty() == false) {
            const auto &cur = q.front();
            const int curX = cur.first;
            const int curY = cur.second;
            q.pop();
            for (auto &dir : dirs) {
                const int dx = dir[0];
                const int dy = dir[1];
                const int nextX = curX + dx;
                const int nextY = curY + dy;
                if (nextX >= 0 && nextX < m && nextY >= 0 && nextY < n && ans[nextX][nextY] == -1) {
                    ans[nextX][nextY] = ans[curX][curY] + 1;
                    q.emplace(nextX, nextY);
                }
            }
        }
        return ans;
    }
};
