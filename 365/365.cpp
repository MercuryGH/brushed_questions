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

class Solution
{
    struct State {
        int a, b;
        State(int a, int b): a(a), b(b) {}
        string toHash() const {
            return std::to_string(a) + " " + std::to_string(b);
        }
    };
    vector<State> getNextStates(const State curState, const int jug1Capacity, const int jug2Capacity) {
        vector<State> nextStates;
        if (curState.a < jug1Capacity)
            nextStates.emplace_back(jug1Capacity, curState.b); // 装满第一个
        if (curState.b < jug2Capacity)
            nextStates.emplace_back(curState.a, jug2Capacity); // 装满第二个

        if (curState.a > 0)
            nextStates.emplace_back(0, curState.b); // 清空第一个
        if (curState.b > 0)
            nextStates.emplace_back(curState.a, 0);

        const int bCanHold = jug2Capacity - curState.b;
        // 从 A 尽可能倒水到 B
        const int waterExchangeA2B = std::min(bCanHold, curState.a);
        if (waterExchangeA2B > 0) 
            nextStates.emplace_back(curState.a - waterExchangeA2B, curState.b + waterExchangeA2B);

        const int aCanHold = jug1Capacity - curState.a;
        // 从 B 尽可能倒水到 A
        const int waterExchangeB2A = std::min(aCanHold, curState.b);
        if (waterExchangeB2A > 0) 
            nextStates.emplace_back(curState.a + waterExchangeB2A, curState.b - waterExchangeB2A);

        return nextStates;
    }
public:
    bool canMeasureWater(int jug1Capacity, int jug2Capacity, int targetCapacity)
    {
        if (targetCapacity == 0) {
            return true;
        }
        if (jug1Capacity + jug2Capacity < targetCapacity) {
            return false;
        }
        State initState{0, 0};
        std::queue<State> q;
        q.push(initState);
        std::unordered_map<string, bool> vis;
        vis[initState.toHash()] = true;

        std::unordered_map<State, State> prevStateTbl;
        // prevStateTbl[initState] = "null";

        while (q.empty() == false) {
            State curState = q.front();
            q.pop();
            if (curState.a == targetCapacity || curState.b == targetCapacity || curState.a + curState.b == targetCapacity) {
                return true;
            }

            vector<State> nextStates = getNextStates(curState, jug1Capacity, jug2Capacity);
            for (const auto nextState : nextStates) {
                if (vis[nextState.toHash()] == false) {
                    vis[nextState.toHash()] = true;
                    q.push(nextState);

                    prevStateTbl[nextState] = curState;
                }
            }
        }
        return false;
    }
};

