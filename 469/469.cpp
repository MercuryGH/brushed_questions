#include <vector>
using std::vector;

/**
 * 凸包模板题
 */
class Solution {
public:
    bool isConvex(vector<vector<int>>& points) {
        const int n = points.size();
        long long pre = 0;
        long long cur = 0;

        for (int i = 0; i < n; i++) {
            const int x1 = points[i][0];
            const int x2 = points[(i + 1) % n][0];
            const int x3 = points[(i + 2) % n][0];
            const int y1 = points[i][1];
            const int y2 = points[(i + 1) % n][1];
            const int y3 = points[(i + 2) % n][1];

            const int dx1 = x2 - x1;
            const int dx2 = x3 - x2;
            const int dy1 = y2 - y1;
            const int dy2 = y3 - y2;

            cur = dx1 * dy2 - dx2 * dy1;
            if (cur != 0) { // 防止 n 点共线的情况发生
                if (cur * pre < 0) { // cur 和 pre 异号
                    return false;
                }
                pre = cur;
            }
        }
        return true;
    }
};
