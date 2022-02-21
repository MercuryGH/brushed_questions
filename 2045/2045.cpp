#include <vector>
#include <unordered_map>
#include <queue>

class Solution
{
    static bool curTimeIsRed(int curTime, int change) {
        return (curTime / change) % 2 == 1;
    }
public:
    int secondMinimum(int n, std::vector<std::vector<int>> &edges, int time, int change)
    {
        std::unordered_map<int, int> fastest;
        std::unordered_map<int, int> secondFastest;

        std::queue<std::pair<int, int>> q;  // (node, time) 元组
        q.push(std::make_pair(1, 0));

        std::unordered_map<int, std::vector<int>> g;  // 用vector实现的邻接表
        
        int fastestTime = -1;

        for (auto &edge : edges) {
            const int startNode = edge[0];
            const int endNode = edge[1];
            if (g.find(startNode) == g.end()) {
                g[startNode] = std::vector<int>(0);  // 构造一个std::vector，初始化为0个元素，赋给 g[startNode]
            }
            if (g.find(endNode) == g.end()) {
                g[endNode] = std::vector<int>(0);
            }
            g[startNode].push_back(endNode);
            g[endNode].push_back(startNode);
        }

        while (q.empty() == false) {
            std::pair<int, int> next = q.front();
            q.pop();
            const int node = next.first;
            const int curTime = next.second;

            for (auto nextNode : g[node]) {
                int destTime = curTime + time;
                if (nextNode == n) {  // 到达终点了
                    if (fastestTime == -1) {  // 最短路
                        fastestTime = destTime;
                    } else {  // 次短路
                        if (destTime > fastestTime) {
                            return destTime;
                        }
                    }
                }
                if (curTimeIsRed(destTime, change) == true) {  // 当前时间是红灯
                    destTime = (destTime / change + 1) * change;  // 等
                }

                if (fastest.find(nextNode) == fastest.end()) {  // 找不到
                    fastest[nextNode] = destTime;
                    q.push(std::make_pair(nextNode, destTime));
                    continue;
                }
                /** 
                 * 次短路可能重复以某个节点为下一节点，需要用 fastest[nextNode] < destTime 保证它比最短路慢才能加入到后面的队列中
                 * 注意理解下面的代码（难点）
                 */
                if (secondFastest.find(nextNode) == secondFastest.end() && fastest[nextNode] < destTime) {
                    secondFastest[nextNode] = destTime;
                    q.push(std::make_pair(nextNode, destTime));
                    continue;
                }
            }
        }
        return -1;
    }
};