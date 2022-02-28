#include <queue>
#include <unordered_map>
#include <vector>
using std::vector;

/**
 * 找出前 k 个高频元素
 * 重点是对键值对 (key, value) = (元素, 频率) 的排序方法
 */
class Solution
{
    /**
     * 堆解法
     * 时间复杂度 O(n log k)
     */
    void solveByHeap(const std::unordered_map<int, int> &hash, int k, vector<int> &ans) {
        const auto cmp = [](std::pair<int, int> p1, std::pair<int, int> p2) {
            return p1.second >= p2.second; // 结果为 true 的会被放到下面
        };
        std::priority_queue<
            std::pair<int, int>,
            vector<std::pair<int, int>>,
            decltype(cmp) // 注意：是小顶堆！！
        > q(cmp);
        for (const auto [num, freq] : hash) {
            if (q.size() == k) {
                const int minFreq = q.top().second;
                if (minFreq < freq) {
                    q.pop();
                    q.push({num, freq});
                }
            } else {
                q.push({num, freq});
            }
        }

        while (q.empty() == false) {
            const int res = q.top().first;
            q.pop();
            ans.push_back(res);
        }
    }
    /**
     * 桶排序解法 
     * 经典空间换时间，时间复杂度 O(n)，空间复杂度为 O(n)
     */
    void solveByBucket(const std::unordered_map<int, int> &hash, int k, int n, vector<int> &ans) {
        // buckets[i] 存放出现频率为 i 的数的集合
        // 注意: buckets[0] 不使用
        vector<vector<int>> buckets(n + 1, vector<int>()); // 虽然是二维数组，但每一维的长度可变，故不会到 n^2 空间

        for (const auto [num, freq] : hash) {
            buckets[freq].push_back(num);
        }

        for (int i = n, cnt = 0; i >= 1; i--) {
            for (const auto num : buckets[i]) {
                if (cnt == k) {
                    break;
                }
                ans.push_back(num);
                cnt++;
            }
            if (cnt >= k) {
                break;
            }
        }
    }

    // 另外还有平均 O(n) 的快排解法，类似 kthMaxElement，但细节比较多，就不写了

public:
    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        std::unordered_map<int, int> hash;
        for (const int num : nums) {
            hash[num]++;
        }

        vector<int> ans; // 可以按 任意顺序 返回答案
        // solveByHeap(hash, k, ans);
        const int n = nums.size();
        solveByBucket(hash, k, n, ans);
        return ans;
    }
};
