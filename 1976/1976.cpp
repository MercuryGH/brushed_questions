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

/**
 * 无向图，求 0 号结点到 n - 1 号结点的最短路的方案数
 * Dijkstra 模板题
 */
class Solution
{
    using ll = long long;
    constexpr static ll MOD = 1e9 + 7;
    constexpr static ll INF = LLONG_MAX;
public:
    int countPaths(int n, vector<vector<int>> &roads)
    {
        vector<vector<pair<ll, ll>>> adjTbl(n);
        for (const auto &road : roads) {
            const int from = road[0];
            const int to = road[1];
            const int dis = road[2];

            adjTbl[from].emplace_back(to, dis);
            adjTbl[to].emplace_back(from, dis);
        }

        // 初始化 dis 数组
        vector<ll> dis(n, INF);
        dis[0] = 0;

        // vis 数组保证每个结点只被展开一次
        // 所有vis[i] = true的结点就是 CLOSE SET 的结点
        vector<bool> vis(n, false);

        // 所有从优先队列中弹出过的结点，自动加入 CLOSE SET
        // 虽然该优先队列可能还有这个结点，但它们都会被vis标记，因此
        // 之后会被自动跳过。
        // 该优先队列的排序规则为：dis小则优先，dis相等则无所谓
        const auto cmp = [](const pair<ll, ll> &a, const pair<ll, ll> &b) {
            return a.second > b.second;
        };
        std::priority_queue<
            pair<ll, ll>,
            vector<pair<ll, ll>>,
            decltype(cmp)
        > q(cmp);
        // 将 0 号结点加入 OPEN SET
        // CLOSE SET 初始时是 EMPTY
        q.emplace(0, 0);

        while (q.empty() == false) {
            // 从OPEN SET中找最小代价的结点，展开其邻接，然后加入CLOSE SET
            const auto [curNode, curDis] = q.top();
            q.pop();
            if (vis[curNode] == true) {
                continue;
            }
            vis[curNode] = true;

            for (const auto [adjNode, adjDis] : adjTbl[curNode]) {
                // CLOSE SET 剪枝
                if (vis[adjNode] == true) {
                    continue;
                }
                if (curDis + adjDis < dis[adjNode]) {
                    dis[adjNode] = curDis + adjDis;
                    // 加入 OPEN SET 
                    //（之后可能被重复加入，但无所谓，只取最近的那条路）
                    q.emplace(adjNode, dis[adjNode]);
                }
            }
        }
        // ll minTime = dis[n - 1];

        // dp[i] 表示从 0 到 i 的最短路径的条数
        // dp[i] = sum(dp[j]) if j to i 经过最短路径
        // 状态更新必须严格按照路径长度递增顺序

        // 按照距离起始点的距离 dis[i] 排序
        vector<pair<ll, ll>> disNodes(n);
        for (int i = 0; i < n; i++) {
            disNodes[i] = {dis[i], i};
        }
        std::sort(disNodes.begin(), disNodes.end());

        vector<int> dp(n, 0);
        dp[0] = 1;
        for (const auto [distance, curNode] : disNodes) {
            for (const auto [adjNode, adjDis] : adjTbl[curNode]) {
                if (dis[adjNode] + adjDis != dis[curNode]) {
                    // 不是最短路径
                    continue;
                }

                dp[curNode] += dp[adjNode];
                dp[curNode] %= MOD;
            }
            if (curNode == n - 1) {
                return dp[curNode];
            }
        }
        return -1;
    }
};

