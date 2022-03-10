#include <vector>
#include <unordered_map>
using std::vector;

/**
 * 和为 k 的子数组
 * 前缀和入门题
 * 
 * 思想：考虑每个a[i]都可能成为至少一个和为 targetSum 的子数组的 **最右边** 的元素。
 * 我们将a[1] + ... + a[i]记为 curSum，
 * 如果我们能够维护一个哈希表，其 
 *   - key 为从a[1]到a[i]，所有可能得到的前缀和 S_0, S_1, ... S_{i-1}；
 *   - value 为得到 key 为前缀和可能的方案数（例如 {1, -1, 1, -1} 有 2 种方案得到 0）
 *   - 注意初始化 prefix[S_0 == 0] = 1.
 * 那么，我们查表，找到key为 curSum - targetSum 的那个 value，减去之，就可以凑出一个合法的子数组，其
 * 元素之和恰为 curSum - (curSum - targetSum) = targetSum. 
 */
class Solution
{
public:
    int subarraySum(vector<int> &nums, int k)
    {
        const int n = nums.size();
        // vector<int> prefix(k, 0); // 用 vector 模拟哈希表太臃肿了
        std::unordered_map<int, int> prefix;
        prefix[0] = 1;

        int curSum = 0;
        int ans = 0;
        for (const auto num : nums) {
            curSum += num;
            if (prefix.find(curSum - k) != prefix.end()) {
                ans += prefix[curSum - k];
            }
            prefix[curSum]++;
        }
        return ans;
    }
};
