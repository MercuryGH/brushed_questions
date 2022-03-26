#include <algorithm>
#include <functional>
#include <ctime>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <list>
#include <string>
using std::vector, std::string;


using dynamic_bitset = vector<uint8_t>; // 替换 vector<bool>
// 没必要放弃 vector<bool>：它可能确实有问题，但如果只是做简单的存取、vis数组，都是OK的，访问速度也不会差（与库函数实现有关）

/**
 * 优先队列 + BFS，一个来自 Dijkstra 的贪心做法
 */
class Solution
{
    struct Entry
    {
        int i, j;
        int val;
        bool operator<(const Entry &other) const
        {
            return this->val > other.val;
        }
        Entry(int i, int j, int val) : i(i), j(j), val(val) {}
    };

    const vector<std::pair<int, int>> dirs{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

public:
    int swimInWater(vector<vector<int>> &grid)
    {
        int n = grid.size();
        std::priority_queue<
            Entry, 
            vector<Entry>, 
            std::function<bool(const Entry &x, const Entry &other)>
        > q(&Entry::operator<);
        vector<dynamic_bitset> vis(n, dynamic_bitset(n, false));

        q.emplace(0, 0, grid[0][0]);
        int ans = 0;
        while (!q.empty())
        {
            Entry cur = q.top();
            q.pop();
            if (vis[cur.i][cur.j] == true)
            {
                continue;
            }

            vis[cur.i][cur.j] = true;
            ans = std::max(ans, grid[cur.i][cur.j]);
            if (cur.i == n - 1 && cur.j == n - 1)
            {
                break;
            }

            for (const auto [di, dj] : dirs)
            {
                const int ni = cur.i + di;
                const int nj = cur.j + dj;
                if (ni >= 0 && ni < n && nj >= 0 && nj < n)
                {
                    if (vis[ni][nj] == false)
                    {
                        q.emplace(ni, nj, grid[ni][nj]);
                    }
                }
            }
        }
        return ans;
    }
};
