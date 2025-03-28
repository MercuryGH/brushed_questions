#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::vector, std::string, std::pair;

/*
给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列。 
*/
class Solution
{
    // 传参 const string &s 比 const string 要快得多！！
    int dp(int &maxLen, int curNode, const vector<vector<int>> &children, const string &s)
    {
        int max = 0;
        int subMax = 0;
        for (const int child : children[curNode])
        {
            if (s[child] == s[curNode])
            {
                // Only DP
                dp(maxLen, child, children, s);
            }
            else
            {
                // DP and update
                const int childDp = dp(maxLen, child, children, s);
                if (childDp > max)
                {
                    subMax = max;
                    max = childDp;
                }
                else if (childDp > subMax)
                {
                    subMax = childDp;
                }
            }
        }
        int res = max + 1;
        maxLen = std::max(maxLen, max + subMax + 1);
        return res;
    }

    static int pointHash(int x, int y) {
        return x * 1000 + y;
    }

    static void handleSquare(std::unordered_set<int> &calcPoints, int cx, int cy, int r) {
        for (int i = cx - r; i <= cx; i++) {
            for (int j = cy - r; j <= cy; j++) {
                if (disSqr(i, j, cx, cy) <= r * r) {
                    calcPoints.insert(pointHash(i, j));
                    calcPoints.insert(pointHash(i, 2 * cy - j));
                    calcPoints.insert(pointHash(2 * cx - i, j));
                    calcPoints.insert(pointHash(2 * cx - i, 2 * cy - j));
                }
            }
        }
    }

public:
    int countLatticePoints(vector<vector<int>>& circles) {
        std::unordered_set<int> calcPoints;

        for (const auto &circle : circles) {
            const int cx = circle[0];
            const int cy = circle[1];
            const int r = circle[2];
            handleSquare(calcPoints, cx, cy, r);
        }

        return calcPoints.size();
    }
};

int main()
{
}

