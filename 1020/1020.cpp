#include <vector>

/**
 * 二维格点中，计算不与边界相连的连通分量的结点总数
 * 如果图会动态地更新结点和边，那么并查集是最好的；但本题的图是静态的，因此不需要用并查集，用并查集反而慢一点
 * 详见 https://cs.stackexchange.com/questions/47596/dfs-vs-union-find-for-computing-connected-components-of-a-static-graph
 * 
 * 要求无向图中连通分量数，详见 https://zhuanlan.zhihu.com/p/90907170
 */
class Solution
{
    const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int n;
    int m;

    bool isOutOfBound(int x, int y)
    {
        return x < 0 || x >= m || y < 0 || y >= n;
    }

    void dfs(const std::vector<std::vector<int>> &grid, std::vector<std::vector<bool>> &vis, int x, int y)
    {
        if (isOutOfBound(x, y))
        {
            return;
        }
        if (grid[x][y] == 0 || vis[x][y] == true)
        {
            return;
        }

        vis[x][y] = true;
        for (const auto &dir : dirs)
        {
            const int dx = dir[0];
            const int dy = dir[1];
            if (isOutOfBound(x + dx, y + dy) == false && grid[x + dx][y + dy] == 1 && vis[x + dx][y + dy] == false) {
                dfs(grid, vis, x + dx, y + dy);
            }
        }
    }

public:
    int numEnclaves(std::vector<std::vector<int>> &grid)
    {
        this->m = grid.size();
        this->n = grid[0].size();
        std::vector<std::vector<bool>> vis(m, std::vector<bool>(n, false));

        // 从边界拓展
        for (int i = 0; i < m; i++)
        {
            if (grid[i][0] == 1 && vis[i][0] == false)
                dfs(grid, vis, i, 0);  // dfs(i, 0);
            if (grid[i][n - 1] == 1 && vis[i][n - 1] == false)
                dfs(grid, vis, i, n - 1);
        }
        for (int j = 1; j < n - 1; j++)
        {
            if (grid[0][j] == 1 && vis[0][j] == false)
                dfs(grid, vis, 0, j);
            if (grid[m - 1][j] == 1 && vis[m - 1][j] == false)
                dfs(grid, vis, m - 1, j);
        }
        // 边界拓展完毕

        int ans = 0;
        for (int i = 1; i < m - 1; i++)
        {
            for (int j = 1; j < n - 1; j++)
            {
                if (grid[i][j] == 1 && vis[i][j] == false)
                {
                    ans++;
                    // 如果是求连通分量数，还需要再调用 dfs()
                }
            }
        }
        return ans;
    }
};
