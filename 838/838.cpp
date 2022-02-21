#include <string>
#include <queue>
#include <vector>
#include <cstdio>
using std::string;

class Solution
{
    int n;
    bool outOfBound(int i)
    {
        return i < 0 || i >= n;
    }
    enum ForceDirection {
        LEFT = -1,
        RIGHT = 1,
        NONE = 0
    };
    struct Force {
        ForceDirection direction;
        int time;  // 产生的时间
        int index;  // 作用的对象的位置
        Force(ForceDirection d, int t, int i): direction(d), time(t), index(i) {}
        int getPropagatedIndex() {
            return direction + index;
        }
    };
    struct Domino {
        Force force;  // 受到的合力（实际可以省略该字段）
        int lastForcedTime;  // 最近一次受力时间
        Domino(Force force, int t): force(force), lastForcedTime(t) {}
        // Domino(Domino &&d) = default;
    };

public:
    string pushDominoes(string dominoes)
    {
        this->n = dominoes.length();
        std::queue<Force> q;  // 仅保存数组下标
        std::vector<Domino> dominoArray;
        for (int i = 0; i < n; i++) {
            ForceDirection direction;
            switch (dominoes[i]) {
                case 'L': direction = LEFT; break;
                case 'R': direction = RIGHT; break;
                default: direction = NONE;
            }
            Force force(direction, 0, i);
            dominoArray.push_back(Domino(force, direction != NONE ? 0 : -1));
            if (direction != NONE) {
                q.push(std::move(force));
            }
        }

        std::string ans(dominoes);
        while (q.empty() == false) {
            Force fetchedForce = q.front();
            q.pop();

            int propagatedIndex = fetchedForce.getPropagatedIndex();
            if (fetchedForce.direction == NONE || outOfBound(propagatedIndex)) {
                continue;
            }

            Domino &forcedDomino = dominoArray[propagatedIndex]; // 注意 & 符号是必须的！！

            if (forcedDomino.lastForcedTime == -1) {
                fetchedForce.time++;
                fetchedForce.index = propagatedIndex;
                q.push(fetchedForce);  // 产生新的力
                forcedDomino.lastForcedTime = fetchedForce.time;
                ans[propagatedIndex] = fetchedForce.direction == LEFT ? 'L' : 'R';
            } else if (forcedDomino.lastForcedTime == fetchedForce.time + 1) {  // 同时受力
                // 不再产生新的力，只写答案数组
                ans[propagatedIndex] = '.';
            }
            // 注意：本算法在处理一个多米诺骨牌同时受力后，并没有立即删除来自其中一个方向的力，
            // 而是让它继续传播一格，然而因为无法进入 q.push() 代码段而自然被消灭
        }
        return ans;
    }
};