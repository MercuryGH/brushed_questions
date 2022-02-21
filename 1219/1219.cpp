#include <vector>
#include <algorithm>

/**
 * 没法优化的暴搜，没有什么好的剪枝方案
 * 本题可以用grid[x][y] = 0来代替 visited[x][y] = true，来避免开一个visited数组
 * 但建议还是使用visited数组，更规范
 */
class Solution
{
    static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int n, m;
    int dfs(int x, int y, std::vector<std::vector<int>> &grid, std::vector<std::vector<bool>> &visited)
    {
        const int curGold = grid[x][y];
        int ans = 0;
        visited[x][y] = true;

        for (int i = 0; i < 4; i++)
        {
            const int nextX = x + dirs[i][0];
            const int nextY = y + dirs[i][1];
            if (nextX >= 0 && nextX < m && nextY >= 0 && nextY < n && grid[nextX][nextY] > 0 && visited[nextX][nextY] == false) {
                ans = std::max(ans, dfs(nextX, nextY, grid, visited));
            }
        }

        visited[x][y] = false;
        grid[x][y] = curGold;  // 回溯
        return curGold + ans;
    }
public:
    int getMaximumGold(std::vector<std::vector<int>> &grid)
    {
        this->m = grid.size();
        this->n = grid[0].size();
        int ans = 0;

        std::vector<std::vector<bool>> visited(m, std::vector(n, false));

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] > 0 && visited[i][j] == false) {
                    ans = std::max(ans, dfs(i, j, grid, visited));
                }
            }
        }
        return ans;
    }
};
