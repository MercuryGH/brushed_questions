#include <vector>
#include <unordered_map>
using std::vector;

/**
 * 和为 k 的子数组
 * 前缀和入门题
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
