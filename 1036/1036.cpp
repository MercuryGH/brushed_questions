#include <vector>
#include <unordered_set>
#include <queue>

/**
 * 当两点相隔较远时，常规泛洪 BFS 做法可能会搜完整个棋盘，会 TLE。
 * 因此，需要考虑算法优化一个搜索上界
 * 在给定 n 个点无法访问的情况下，可以证明，这些无法访问的点若围成了一个封闭区域，
 * 则这个封闭区域的面积不超过 S_n = n * (n-1) / 2
 * 
 * 因此，从起点和终点出发，若均能BFS搜索出 S_n + 1 个点可达，
 * 则说明无法访问的点并没有围出针对起点和终点的封闭区域，输出true；否则输出false
 */
class Solution
{
    int maxItr;
    static const int MAXN = 1e6;
    const int directions[4][2] = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };

    std::unordered_set<long long> blockedPoints;
public:
    static long long getHashCode(const int x, const int y)
    {
        const long long BASE = 114514;
        return x * BASE + y;
    }
    static bool isSamePoint(const int x1, const int y1, const int x2, const int y2) {
        return x1 == x2 && y1 == y2;
    }
    static bool outOfBound(const int x, const int y) {
        return x < 0 || x >= MAXN || y < 0 || y >= MAXN;
    }
    bool isEscapePossible(std::vector<std::vector<int>> &blocked, std::vector<int> &source, std::vector<int> &target)
    {
        for (const auto &point : blocked) {
            blockedPoints.insert(getHashCode(point[0], point[1]));
        }
        const int n = blocked.size();
        maxItr = n * (n - 1) / 2;
        return canReach(source, target) && canReach(target, source);
    }
    /**
     * 从点 start 开始，看看能不能抵达 end
     */
    bool canReach(const std::vector<int> &start, const std::vector<int> &end)
    {
        const int x2 = end[0];
        const int y2 = end[1];

        std::unordered_set<long long> vis; // 用HashCode的格式保存已访问的点
        std::queue<std::pair<int, int>> q;

        q.push({start[0], start[1]});
        vis.insert(getHashCode(start[0], start[1]));

        while (q.empty() == false && vis.size() <= maxItr) {
            const auto nextPoint = q.front();
            q.pop();
            const int x1 = nextPoint.first;
            const int y1 = nextPoint.second;
            if (isSamePoint(x1, y1, x2, y2)) {
                return true;
            }

            for (int i = 0; i < 4; i++) {
                const int nextX = x1 + directions[i][0];
                const int nextY = y1 + directions[i][1];
                const int nextPointHashCode = getHashCode(nextX, nextY);
                if (outOfBound(nextX, nextY)) {
                    continue;
                }

                if (vis.count(getHashCode(nextX, nextY))) {  // vis中已经有这个点了
                    continue;
                }

                if (blockedPoints.count(getHashCode(nextX, nextY))) {  // 用 s.find() != s.end() 会更好
                    continue;
                }

                q.push({nextX, nextY});
                vis.insert(getHashCode(nextX, nextY));
            }
        }
        return vis.size() > maxItr;
    }
};