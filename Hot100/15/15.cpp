#include <vector>
#include <algorithm>

/**
 * 3sum
 * 最好的想法：排序后双指针 O(n^2)
 * 详见 https://mp.weixin.qq.com/s/fSyJVvggxHq28a0SdmZm6Q
 */
class Solution
{
    /**
     * 返回已排序数组 nums 的不同的 nums[l] + nums[r] = target 元组 (nums[l], nums[r]). 
     */
    std::vector<std::vector<int>> twoSumTarget(const std::vector<int> &nums, const int start, const int target)
    {
        // nums 数组必须有序
        int lo = start;
        int hi = nums.size() - 1;
        std::vector<std::vector<int>> res;
        while (lo < hi)
        {
            const int lNum = nums[lo];
            const int rNum = nums[hi];
            const int sum = lNum + rNum;
            if (sum < target)
            {
                while (lo < hi && nums[lo] == lNum)
                {
                    lo++;
                }
            }
            else if (sum > target)
            {
                while (lo < hi && nums[hi] == rNum)
                {
                    hi--;
                }
            }
            else
            {
                res.push_back({lNum, rNum});
                while (lo < hi && nums[lo] == lNum)
                {
                    lo++;
                }
                while (lo < hi && nums[hi] == rNum)
                {
                    hi--;
                }
            }
        }
        return res;
    }

public:
    std::vector<std::vector<int>> threeSum(std::vector<int> &nums)
    {
        std::sort(nums.begin(), nums.end());
        const int n = nums.size();
        constexpr int target = 0;

        std::vector<std::vector<int>> ans;
        for (int i = 0; i < n; i++)
        {
            std::vector<std::vector<int>> tuples = twoSumTarget(nums, i + 1, target - nums[i]);
            for (auto &tuple : tuples)
            {
                tuple.push_back(nums[i]);
                ans.push_back(tuple);
            }
            while (i < n - 1 && nums[i] == nums[i + 1])
            {
                i++;
            }
        }
        return ans;
    }
};