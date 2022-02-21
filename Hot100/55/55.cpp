#include <algorithm>
#include <vector>

/**
 * 本人第一次思考时想到了 O(n * mean(a_i)), O(n) 的动态规划解
 * 很拉。因为这题只需要 O(n), O(1) 就可以了
 * 核心特性：如果一个位置能够到达，那么这个位置左侧所有位置都能到达
 */
class Solution
{
public:
    bool canJump(std::vector<int> &nums)
    {
        const int n = nums.size();

        int furthest = 0;
        for (int i = 0; i < n; i++) {
            if (i > furthest) {
                return false;
            }
            furthest = std::max(furthest, i + nums[i]);  // 只需维护最远的即可
        }
        return true;
    }
};