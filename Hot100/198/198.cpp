#include <vector>
#include <algorithm>

class Solution {
public:
    int rob(std::vector<int>& nums) {
        const int n = nums.size();
        if (n == 0) {
            return 0;
        }
        if (n == 1) {
            return nums[0];
        }

        int first = nums[0];
        int second = std::max(nums[0], nums[1]);
        for (int i = 2; i < n; i++) {
            int temp = second;
            second = std::max(first + nums[i], second);
            first = temp;
        }
        return second;
    }
};