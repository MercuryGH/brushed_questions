#include <vector>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <ctime>
using std::vector;

class Solution
{
    void recursivelyGetAncestor(vector<std::unordered_set<int>> &ancestors, int from, int to) {
        ancestors[to].insert(from);
        for (const int ancestorOfFrom : ancestors[from]) {
            ancestors[to].insert(ancestorOfFrom);
        }
    }
public:
    vector<vector<int>> getAncestors(int n, vector<vector<int>> &edges)
    {
        vector<int> inDegrees(n, 0);
        vector<vector<int>> adjTbl(n);
        std::queue<int> q;

        for (const auto &edge : edges) {
            const int from = edge[0];
            const int to = edge[1];
            inDegrees[to]++;
            adjTbl[from].push_back(to);
        }
        for (int i = 0; i < n; i++) {
            if (inDegrees[i] == 0) {
                q.push(i);
            }
        }
        
        vector<std::unordered_set<int>> ancestors(n);
        while (q.empty() == false) {
            const int nextNode = q.front();
            q.pop();

            for (const int adjNode : adjTbl[nextNode]) {
                inDegrees[adjNode]--;

                recursivelyGetAncestor(ancestors, nextNode, adjNode);

                if (inDegrees[adjNode] == 0) {
                    q.push(adjNode);
                }
            }
        }

        vector<vector<int>> ans;

        for (const auto v : ancestors) {
            std::vector<int> tmp;
            tmp.assign(v.begin(), v.end());
            std::sort(tmp.begin(), tmp.end());
            ans.push_back(tmp);
        }

        return ans;
    }
};