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

const int dirs[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
int n, m, x, y, z, w;

struct Point
{
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
    bool equals(const Point &p) const
    {
        return x == p.x && y == p.y;
    }
    bool outOfBound() const
    {
        return x < 1 || x > n || y < 1 || y > m;
    }
};

void dfs(int &miniMax, int &curMax, const vector<vector<int>> &grid, vector<vector<int>> &memo, vector<vector<bool>> &vis, const Point cur, const Point end)
{
    if (cur.equals(end))
    {
        miniMax = std::min(miniMax, curMax);
        return;
    }
    if (curMax >= miniMax) {
        return;
    }

    for (const auto &dir : dirs)
    {
        Point next(cur.x + dir[0], cur.y + dir[1]);

        if (next.outOfBound() == false && vis[next.x][next.y] == false && curMax < memo[next.x][next.y])
        {
            memo[next.x][next.y] = curMax;

            const int tmp = curMax;
            curMax = std::max(curMax, grid[next.x][next.y]);
            vis[next.x][next.y] = true;
            dfs(miniMax, curMax, grid, memo, vis, next, end);
            vis[next.x][next.y] = false;
            curMax = tmp;
        }
    }
}

constexpr int INF = 0x3f3f3f3f;

// minimax all possible way
int getMinimumDay(const vector<vector<int>> &grid, const Point start, const Point end)
{
    int curMax = grid[start.x][start.y];
    int ans = INF;
    vector<vector<bool>> vis(n + 1, vector<bool>(m + 1, false));
    vector<vector<int>> memo(n + 1, vector<int>(m + 1, INF)); // memo[i][j] maintains the minimax path to reach dest.
    dfs(ans, curMax, grid, memo, vis, start, end);
    return ans;
}

int main()
{

    std::cin >> n >> m >> x >> y >> z >> w;

    vector<vector<int>> grid(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            std::cin >> grid[i][j];
        }
    }

    std::cout << getMinimumDay(grid, Point(x, y), Point(z, w)) << "\n";

    return 0;
}