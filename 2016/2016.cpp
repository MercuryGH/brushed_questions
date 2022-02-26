#include <vector>
#include <algorithm>
using std::vector;

/**
 * 求 max(nums[j] - nums[i]), 其中 i < j
 * 若序列不增，直接返回-1
 * 
 * 思路：维护当前指针的左侧的最小元素。O(n)可解
 */
class Solution {
public:
    int maximumDifference(vector<int>& nums) {
        const int n = nums.size();

        int leftMin = INT_MAX;
        int ans = -1;
        for (int i = 0; i < n; i++) {
            const int curNum = nums[i];
            if (curNum == leftMin) {
                continue;
            }

            ans = std::max(ans, curNum - leftMin);
            leftMin = std::min(leftMin, curNum);
        }
        return ans;
    }
};