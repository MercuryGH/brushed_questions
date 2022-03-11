#include <vector>
#include <algorithm>

/**
 * 接雨水，经典DP
 * 朴素方法模拟接雨水的过程，时间复杂度为 O(n * h)
 * DP法只需 O(n).
 */
class Solution
{
public:
    int trap(std::vector<int> &height)
    {
        const int n = height.size();
        std::vector<int> lMaxHeight(n);
        lMaxHeight[0] = 0;
        std::vector<int> rMaxHeight(n);
        rMaxHeight[n - 1] = 0;

        for (int i = 1; i < n; i++) {
            lMaxHeight[i] = std::max(lMaxHeight[i - 1], height[i - 1]);
        }
        for (int i = n - 2; i >= 0; i--) {
            rMaxHeight[i] = std::max(rMaxHeight[i + 1], height[i + 1]);
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += std::max(std::min(lMaxHeight[i], rMaxHeight[i]) - height[i], 0);
        }
        return ans;
    }
};
