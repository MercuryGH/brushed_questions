#include <vector>
#include <algorithm>

/**
 * 从 n 个元素里找 k 个，使得 k 个元素最大差值最小。
 * 最大值最小化问题，很容易想到二分答案。
 * 但本题排序后，可以证明这 k 个元素必然是有序数组中（排序后）的连续段，直接滑动窗口遍历即可
 * 不需要二分答案了
 */
class Solution
{
public:
    int minimumDifference(std::vector<int> &nums, int k)
    {
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        int ans = INT_MAX;
        for (int i = 0; i + k - 1 < n; i++) {
            ans = std::min(ans, nums[i + k - 1] - nums[i]);
        }
        return ans;
    }
};