#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::vector, std::string, std::pair;

class Solution {
    static int disSqr(int x, int y, int cx, int cy) {
        return (x - cx) * (x - cx) + (y - cy) * (y - cy);
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

/*
PB19061341
niuniu123456
*/