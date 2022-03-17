#include <algorithm>
#include <ctime>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <memory>
using std::vector, std::string;

struct Enemy {
    int x, y;
    Enemy(int x, int y): x(x), y(y) {}
};

int sqrDistance(Enemy e) {
    return e.x * e.x + e.y * e.y;
}

inline bool upJudger(Enemy e) {
    return e.y >= std::abs(e.x);
}
inline bool rightJudger(Enemy e) {
    return e.x >= std::abs(e.y);
}
inline bool downJudger(Enemy e) {
    return -e.y >= std::abs(e.x);
}
inline bool leftJudger(Enemy e) {
    return -e.x >= std::abs(e.y);
}

int solution(string &direction, int radius, vector<int> &X, vector<int> &Y)
{
    const int n = X.size();
    vector<Enemy> enemys;
    for (int i = 0; i < n; i++) {
        enemys.emplace_back(X[i], Y[i]);
    }

    const char dir = direction[0];
    int ans = 0;
    bool (*judger)(Enemy e) = upJudger;
    switch (dir) {
        case 'U': {
            judger = upJudger;
            break;
        }
        case 'D': {
            judger = downJudger;
            break;
        } 
        case 'L': {
            judger = leftJudger;
            break;
        }
        case 'R': {
            judger = rightJudger;
            break;
        }
        default: break;
    }
    for (const Enemy enemy : enemys) {
        if (judger(enemy) && sqrDistance(enemy) <= radius * radius) {
            ans++;
        }
    }
    return ans;
}

int main()
{
    return 0;
}