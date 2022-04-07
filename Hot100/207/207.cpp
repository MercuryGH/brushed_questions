#include <vector>
#include <queue>
using std::vector;

/**
 * 拓扑排序例题
 * 经典BFS做法
 */
class Solution
{
public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<int> inDegrees(numCourses, 0);  // 入度
        vector<vector<int>> adjTbl(numCourses);  // 邻接表
        std::queue<int> q; 

        for (const auto &edge : prerequisites) {
            const int to = edge[0];
            const int from = edge[1];
            inDegrees[to]++;
            adjTbl[from].push_back(to);
        }
        for (int i = 0; i < numCourses; i++) { // 用 i 来指代结点
            if (inDegrees[i] == 0) {
                q.push(i);
            }
        }

        while (q.empty() == false) {
            const int nextNode = q.front();
            q.pop();
            numCourses--;  // 成功修读一门课程
            for (const int adjNode : adjTbl[nextNode]) {
                inDegrees[adjNode]--;
                if (inDegrees[adjNode] == 0) {
                    q.push(adjNode);
                }
            }
        }
        return numCourses == 0;
    }

    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adjTbl(numCourses);
        vector<int> inDegrees(numCourses, 0);

        for (const auto &edge : prerequisites) {
            const int from = edge[1];
            const int to = edge[0];
            adjTbl[from].push_back(to);
            inDegrees[to]++;
        }

        vector<int> order;
        vector<bool> vis(numCourses, false);
        std::queue<int> q;
        int learnedCnt = 0;
        for (int i = 0; i < numCourses; i++) {
            if (inDegrees[i] == 0) {
                q.push(i);
                vis[i] = true;
            }
        }
        
        while (q.empty() == false) {
            int curNode = q.front();
            q.pop();
            order.push_back(curNode);
            learnedCnt++;
            for (const int nextNode : adjTbl[curNode]) {
                inDegrees[nextNode]--;
                if (vis[nextNode] == false && inDegrees[nextNode] == 0) {
                    q.push(nextNode);
                    vis[nextNode] = true;
                }
            }
        }

        if (learnedCnt == numCourses) {
            return order;
        }
        return {};
    }
};
