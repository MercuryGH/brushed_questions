#include <vector>
#include <unordered_map>

/**
 * 思路：读到一个数，即便找不到之前与之相加恰好等于结果的数，也要把它存下来到哈希表里
 * 这是 O(n) 的在线算法
 */
class Solution
{
public:
    std::vector<int> twoSum(std::vector<int> &nums, int target)
    {
        std::unordered_map<int, int> hashtable;  // key: 元素的值, value: 数组下标
        for (int i = 0; i < nums.size(); ++i)
        {
            const auto it = hashtable.find(target - nums[i]);
            if (it != hashtable.end())
            {
                return {it->second, i};
            }
            hashtable[nums[i]] = i;
        }
        return {};
    }
};
