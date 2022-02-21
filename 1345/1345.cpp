#include <vector>
#include <unordered_map>
#include <queue>

/**
 * 可以进行 前后跳 和 等值跳 
 * 一般方法为 BFS + hash 空间换时间优化
 * 这道题比较奇怪且偏门，所以并没有完全搞懂
 */
class Solution {
    const int INF = 0x3f3f3f3f;
public:
    int minJumps(std::vector<int>& arr) {
        const int n = arr.size();
        std::unordered_map<int, std::vector<int>> valHasIndices;
        for (int i = n - 1; i >= 0; i--) {
            const int arrVal = arr[i];
            valHasIndices[arrVal].push_back(i);
        }

        std::vector<int> dist(n, INF);
        dist[0] = 0;
        std::queue<int> q;
        q.push(0);

        while (q.empty() == false) {
            const int curIndex = q.front();
            q.pop();
            const int step = dist[curIndex];

            if (curIndex == n - 1) {  // 到最后了
                return step;
            }
            if (curIndex + 1 < n && dist[curIndex + 1] == INF) {  // 往右跳
                q.push(curIndex + 1);
                dist[curIndex + 1] = step + 1;
            }
            if (curIndex - 1 >= 0 && dist[curIndex - 1] == INF) {  // 往左跳
                q.push(curIndex - 1);
                dist[curIndex - 1] = step + 1;
            }
            const auto &indexList = valHasIndices[arr[curIndex]];
            for (auto index : indexList) {
                if (dist[index] == INF) {
                    q.push(index);
                    dist[index] = step + 1;
                }
            }
            valHasIndices.erase(arr[curIndex]);
        }
        return -1;
    }
};