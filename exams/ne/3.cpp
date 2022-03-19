/**
 * 寄了，代码段错误调不出来
 */

#include <algorithm>
#include <ctime>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <stack>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::vector, std::string;

struct Point
{
    int x;
    int y;
    Point() : x(-1), y(-1) {}
    Point(int x, int y) : x(x), y(y) {}
    string hashPoint()
    {
        return std::to_string(x) + " " + std::to_string(y);
    }
};

struct Friend
{
    Point point;
    int moveDistance;
    Friend(Point point, int moveDistance) : point(point), moveDistance(moveDistance) {}
    Friend(int moveDistance) : moveDistance(moveDistance) {}
};

struct Solution
{
    const int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int ans = 0x3f3f3f3f;
    bool hasAns = false;

    bool outOfBound(int x, int y, const vector<vector<int>> &grid)
    {
        const int n = grid.size();
        const int m = grid[0].size();
        return x < 0 || x >= n || y < 0 || y >= m;
    }

    bool isEnemyPoint(Point p, const vector<Point> &enemies, const vector<bool> &killed, int &index)
    {
        for (int i = 0; i < enemies.size(); i++)
        {
            if (killed[i])
            {
                continue;
            }

            if (enemies[i].x == p.x && enemies[i].y == p.y)
            {
                index = i;
                return true;
            }
        }
        return false;
    }

    void dfs(vector<vector<int>> &grid, vector<Friend> &friends, const vector<Point> &enemies, vector<bool> &killed, int remainedEnemyCnt, int stepSum, int actionIndex)
    {
        if (remainedEnemyCnt == 0)
        {
            hasAns = true;
            ans = std::min(ans, stepSum);
            return;
        }

        for (int i = actionIndex; i < friends.size(); i++)
        {
            Friend f = friends[i];

            // bfs in dfs, OMG
            std::queue<Point> q;
            std::vector<int> reachEnemyIndices;
            std::vector<int> reachEnemySteps;
            q.push(f.point);
            int step = 0;
            while (q.empty() == false && step < f.moveDistance)
            {
                int levelSize = q.size();
                Point nextPoint = q.front();
                q.pop();

                int index = -1;
                if (isEnemyPoint(nextPoint, enemies, killed, index))
                { // can reach enemy
                    reachEnemyIndices.push_back(index);
                    reachEnemySteps.push_back(step);
                }

                while (levelSize--)
                {
                    for (const auto &dir : dirs)
                    {
                        const int nx = nextPoint.x + dir[0];
                        const int ny = nextPoint.y + dir[1];
                        if (outOfBound(nx, ny, grid) == false && grid[nx][ny] != -3)
                        {
                            q.emplace(nx, ny);
                        }
                    }
                    step++;
                }
            }

            for (int i = 0; i < reachEnemyIndices.size(); i++)
            {
                const int enemyIndex = reachEnemyIndices[i];
                const int step = reachEnemySteps[i];

                killed[enemyIndex] = true;
                dfs(grid, friends, enemies, killed, remainedEnemyCnt - 1, stepSum + step, i + 1);
                killed[enemyIndex] = false;
            }
        }
    }
};

int main()
{
    freopen("testdata.in", "r", stdin);

    int t;
    std::cin >> t;
    while (t--)
    {
        int n, m, a, b;
        std::cin >> n >> m >> a >> b;
        if (b > a)
        {
            std::cout << -1 << "\n";
            continue;
        }

        vector<vector<int>> grid(n, vector<int>(m));

        vector<Friend> friends;
        for (int i = 0; i < a; i++)
        {
            int moveDistance;
            std::cin >> moveDistance;
            friends.emplace_back(moveDistance);
        }

        vector<Point> enemies;
        vector<bool> killed(enemies.size(), false);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                char c;
                std::cin >> c;
                if (c == '+')
                {
                    grid[i][j] = 0;
                }
                else if (c == 'W')
                {
                    grid[i][j] = -3; // obstacle
                }
                else if (c == 'E')
                {
                    grid[i][j] = -2; // enemy
                    enemies.emplace_back(i, j);
                }
                else
                {
                    int index = c - '0';
                    grid[i][j] = index; // friend
                    friends[index].point = Point(i, j);
                }
            }
        }

        Solution s;
        s.dfs(grid, friends, enemies, killed, b, 0, 0);
        if (s.hasAns)
        {
            std::cout << s.ans << "\n";
        }
        else
        {
            std::cout << -1 << "\n";
        }
    }

    return 0;
}