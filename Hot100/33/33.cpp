#include <vector>

/**
 * 搜索旋转排序数组，特殊的二分查找题目
 * 算法设计很巧妙，建议反复看Leetcode题解
 */
class Solution
{
public:
    int search(std::vector<int> &nums, int target)
    {
        const int n = nums.size();

        int l = 0;
        int r = n - 1;
        while (true)
        {
            if (l > r)
            {
                return -1;
            }

            const int mid = (l + r) / 2;
            if (nums[mid] == target)
            {
                return mid;
            }

            if (nums[0] <= nums[mid])
            { // mid 左侧数组有序
                if (nums[0] <= target && target <= nums[mid])
                {
                    r = mid - 1;
                }
                else
                {
                    l = mid + 1;
                }
            }
            else
            { // mid 右侧数组有序
                if (nums[mid] <= target && target <= nums[n - 1])
                {
                    l = mid + 1;
                }
                else
                {
                    r = mid - 1;
                }
            }
        }
    }
};
