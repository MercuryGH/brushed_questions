#include <queue>
#include <vector>
using std::vector;

class Solution
{
    int n, m;
    int dirs[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    bool outOfBound(int x, int y) {
        return x < 0 || x >= n || y < 0 || y >= m;
    }
public:
    int numIslands(vector<vector<char>> &grid)
    {
        n = grid.size();
        m = grid[0].size();
        std::queue<std::pair<int, int>> q;

        int cnt = 0; // 每个岛屿的专属标记
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == '0' || grid[i][j] == 'X') {
                    continue;
                }

                q.push({i, j});
                grid[i][j] = 'X';
                while (q.empty() == false)
                {
                    const auto [x, y] = q.front();
                    q.pop();

                    for (const auto &dir : dirs) {
                        const int nx = x + dir[0];
                        const int ny = y + dir[1];
                        if (outOfBound(nx, ny) || grid[nx][ny] == '0' || grid[nx][ny] == 'X') {
                            // 避免越界，搜到水和重复搜索
                            continue;
                        }

                        q.push({nx, ny});
                        grid[nx][ny] = 'X';
                    }
                }
                cnt++;
            }
        }

        return cnt;
    }
};