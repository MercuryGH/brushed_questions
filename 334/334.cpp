#include <vector>

/**
 * 解法1：求LIS的长度，然后与3比较，时间复杂度 O(n log n)
 * 解法2：优化LIS。时间复杂度 O(n)
 */ 
class Solution
{
public:
    /**
     * f数组的长度被压缩为2，即只使用 f[0], f[1], f[2]
     * f[k] = x 表示长度为k的上升子序列的最小结尾元素为 x
     * 动态更新f数组即可
     */
    bool increasingTriplet(std::vector<int> &nums)
    {
        int n = nums.size();
        std::vector<int> f(3, INT_MAX);  // 初始化 3 个 INT_MAX (2^31 - 1)
        for (auto num : nums) {
            if (num > f[2]) {
                return true;
            }

            if (num > f[1] && num < f[2]) {
                f[2] = num;
            }
            if (num < f[1]) {
                f[1] = num;
            }
        }
        return false;
    }
};