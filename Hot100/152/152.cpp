#include <vector>
#include <algorithm>

class Solution {
public:
    int maxProduct(std::vector<int>& nums) {
        const int n = nums.size();
        int dp1 = nums[0];
        int dp2 = nums[0];
        int ans = nums[0];
        for (int i = 1; i < n; ++i) {
            const int curDp1 = dp1;
            const int curDp2 = dp2;
            dp1 = std::max(curDp1 * nums[i], std::max(nums[i], curDp2 * nums[i]));
            dp2 = std::min(curDp2 * nums[i], std::min(nums[i], curDp1 * nums[i]));
            ans = std::max(dp1, ans);
        }
        return ans;
    }
};

