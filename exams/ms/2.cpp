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

int solution(int N, vector<int> &A, vector<int> &B)
{
    const int m = A.size();
    vector<int> inDegrees(N, 0);
    vector<vector<int>> adjTbl(N);
    vector<bool> vis(N, false);
    std::queue<int> q;

    for (int i = 0; i < m; i++) {
        const int n1 = A[i];
        const int n2 = B[i];
        inDegrees[n1]++;
        inDegrees[n2]++;
        adjTbl[n1].push_back(n2);
        adjTbl[n2].push_back(n1);
    }
    for (int i = 0; i < N; i++) {
        if (inDegrees[i] == 0 || inDegrees[i] == 1) {
            q.push(i);
            vis[i] = true;
        }
    }

    int ans = 0;
    while (q.empty() == false) {
        int curDisappearSize = q.size();
        while (curDisappearSize--) {
            const int nextNode = q.front();
            q.pop();
            // std::cout << nextNode << " ";

            for (const int adjNode : adjTbl[nextNode]) {
                inDegrees[adjNode]--;
                if (vis[adjNode] == false && (inDegrees[adjNode] == 0 || inDegrees[adjNode] == 1)) {
                    q.push(adjNode);
                    vis[adjNode] = true;
                }
            }
        }
        // std::cout << "\n";
        ans++;
    }
    return ans;
}

int main()
{
    vector<int> A = {0, 1, 2, 1, 4, 4};
    vector<int> B = {1, 2, 0, 4, 5, 6};
    std::cout << solution(7, A, B) << "\n";
    return 0;
}