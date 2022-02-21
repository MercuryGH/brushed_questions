#include <vector>
#include <algorithm>

/**
 * 双指针例题之一，O(n^2)暴力可解
 * 双指针只需O(n)。思想：
 * 1. 初始化为容器两端
 * 2. 每次向内移动短板，若答案更大，则更新
 * 可以证明，这样不会丢失最优解。详见LeetCode题解
 */
class Solution
{
public:
    int maxArea(std::vector<int> &height)
    {
        int i = 0;
        int j = height.size() - 1;
        int ans = 0;
        while (true) {
            if (i >= j) {
                break;
            }
            const int lHeight = height[i];
            const int rHeight = height[j];
            if (lHeight < rHeight) {
                ans = std::max(ans, (j - i) * lHeight);
                i++;
            } else {
                ans = std::max(ans, (j - i) * rHeight);
                j--;
            }
        }
        return ans;
    }
};