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
    int val;
    Point(int x, int y, int val) : x(x), y(y), val(val) {}
};

struct Area
{
    std::vector<Point> points;

    bool containsNumber(int num) const
    {
        for (const auto &point : points)
        {
            if (point.val == num)
            {
                return true;
            }
        }
        return false;
    }

    bool containsPoint(int x, int y) const
    {
        for (const auto &p : points)
        {
            if (x == p.x && y == p.y)
            {
                return true;
            }
        }
        return false;
    }
};

struct Solution
{
    bool hasAnswer = false;
    bool uniqueAnswer = false;
    vector<string> prevAns;

    Area getPointArea(const int x, const int y, const vector<Area> &areas)
    {
        for (const auto &area : areas)
        {
            if (area.containsPoint(x, y))
            {
                return area;
            }
        }
        // exception
        std::cout << "WTF\n";
        return areas[0];
    }

    // check if putting val in (x, y) is valid in current grid and areas
    bool check(const vector<vector<int>> &grid, const vector<Area> &areas, int x, int y, int val)
    {
        if (grid[x][y] != -1)
        {
            return false;
        }

        // judge cross
        for (int i = 0; i < 3; i++)
        {
            if (i == x)
            {
                continue;
            }

            if (grid[i][y] == val)
            {
                return false;
            }
        }

        for (int j = 0; j < 3; j++)
        {
            if (j == y)
            {
                continue;
            }

            if (grid[x][j] == val)
            {
                return false;
            }
        }

        // judge area
        Area area = getPointArea(x, y, areas);
        if (area.containsNumber(val) == true)
        {
            return false;
        }

        return true;
    }

    void printGrid(const vector<vector<int>> &grid)
    {
        std::cout << "**********\n";

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                std::cout << grid[i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    bool checkSameAnswer(const vector<vector<int>> &grid)
    {
        for (const auto &ansStr : prevAns)
        {
            string curAns;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    curAns += std::to_string(grid[i][j]);
                }
            }

            if (curAns != ansStr)
            {
                return false;
            }
        }
        return true;
    }

    void dfs(vector<vector<int>> &grid, vector<vector<bool>> &vis, const vector<Area> &areas, int remainedCnt)
    {
        if (hasAnswer && !uniqueAnswer)
        {
            return;
        }

        if (remainedCnt == 0)
        { // all filled
            if (hasAnswer == false)
            {
                string curAns;
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        curAns += std::to_string(grid[i][j]);
                    }
                }
                prevAns.push_back(curAns);
            }

            hasAnswer = true;
            uniqueAnswer = true;

            // check if all answer are truely the same
            if (checkSameAnswer(grid) == false)
            {
                uniqueAnswer = false;
            }

            return;
        }

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (vis[i][j] == false && grid[i][j] == -1)
                {
                    for (int val = 1; val <= 3; val++)
                    {
                        if (check(grid, areas, i, j, val) == true)
                        {
                            vis[i][j] = true;
                            grid[i][j] = val;
                            dfs(grid, vis, areas, remainedCnt - 1);
                            grid[i][j] = -1;
                            vis[i][j] = false;
                        }
                    }
                }
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
        vector<vector<int>> grid(3, vector<int>(3));
        int filledCnt = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                char c;
                std::cin >> c;
                if (c == '*')
                {
                    grid[i][j] = -1; // to be filled
                }
                else
                {
                    filledCnt++;
                    grid[i][j] = c - '0';
                }
            }
        }
        const int remainedCnt = 9 - filledCnt;

        vector<Area> areas;
        for (int i = 0; i < 3; i++) // Area
        {
            Area area;
            for (int j = 0; j < 3; j++)
            { // Points in the area
                int x, y;
                std::cin >> x >> y;
                Point point(x, y, grid[x][y]);
                area.points.push_back(point);
            }
            areas.push_back(area);
        }

        vector<vector<bool>> vis(3, vector<bool>(3, false));

        Solution s;
        s.dfs(grid, vis, areas, remainedCnt);
        if (s.uniqueAnswer)
        {
            std::cout << "Unique\n";
            string ans = s.prevAns[0];
            for (int i = 0; i < 9; i += 3)
            {
                for (int j = 0; j < 3; j++)
                {
                    std::cout << ans[i + j];
                }
                std::cout << "\n";
            }
        }
        else if (s.hasAnswer)
        {
            std::cout << "Multiple\n";
        }
        else
        {
            std::cout << "No\n";
        }
    }

    return 0;
}
/*
4
*2*
1*2
***
0 0 0 1 1 0
0 2 1 1 1 2
2 0 2 1 2 2
**3
***
***
0 0 1 0 1 1
0 1 0 2 1 2
2 0 2 1 2 2
**3
1**
**2
0 0 1 0 1 1
0 1 0 2 1 2
2 0 2 1 2 2
3*3
1**
**2
0 0 1 0 1 1
0 1 0 2 1 2
2 0 2 1 2 2
*/