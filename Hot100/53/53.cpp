#include <vector>
#include <algorithm>

/**
 * 最大子列和
 */
class Solution
{
public:
    int maxSubArray(std::vector<int> &nums)
    {
        const int n = nums.size();

        int ans = nums[0];
        int cur = nums[0];
        for (int i = 1; i < n; i++) {
            cur = std::max(cur + nums[i], nums[i]);
            ans = std::max(cur, ans);
        }
        return ans;
    }
};