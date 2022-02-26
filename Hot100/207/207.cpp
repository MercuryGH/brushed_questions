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
};
