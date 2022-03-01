#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
using std::vector;

/**
 * 贪心 模拟
 */
class Solution {
public:
    int leastInterval(vector<char> &tasks, int cd) {
        std::unordered_map<char, int> hash;
        for (const char c : tasks) {
            hash[c]++;
        }

        const int m = hash.size(); // 任务总类数
        vector<int> nextValid(m, 1); // nextValid[i] 表示第 i 个任务下次最早可以执行的时刻
        vector<int> rest; // rest[i] 表示第 i 个任务的剩余个数
        for (const auto [task, taskNum] : hash) {
            rest.push_back(taskNum);
        }

        int time = 0;
        int n = tasks.size();
        while (n--) {
            time++;
            int minNextValid = INT_MAX;
            for (int j = 0; j < m; j++) {
                if (rest[j]) {
                    minNextValid = std::min(minNextValid, nextValid[j]);
                }
            }
            time = std::max(time, minNextValid); // 计算冷却时间
            int best = -1;
            // 选出最合适的任务（当前可以执行，且剩余个数最多）
            for (int j = 0; j < m; j++) {
                if (rest[j] > 0 && nextValid[j] <= time) {
                    if (best == -1 || rest[j] > rest[best]) {
                        best = j;
                    }
                }
            }
            nextValid[best] = time + cd + 1;
            rest[best]--;
        }

        return time;
    }
};
