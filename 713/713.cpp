#include <unordered_map>
#include <vector>
using std::vector;

class Solution
{
public:
    /**
     * @brief 找出nums，乘积小于 k 的的子数组的个数
     * 保证nums[i] >= 0
     * 
     * 二分前缀和的时间复杂度为O(n log n)，滑动窗口仅需 O(n)
     */
    int numSubarrayProductLessThanK(vector<int> &nums, int k)
    {
        if (k <= 1) {
            return 0;
        }
        const int n = nums.size();

        int ans = 0;
        int l = 0;
        int r = 0;
        int acc = 1;
        while (true) {
            if (r >= n) {
                break;
            }
            acc *= nums[r];
            while (true) {
                if (acc < k) {
                    break;
                }
                acc /= nums[l];
                l++;
            }
            ans += r - l + 1;
            r++;
        }
        return ans;
    }
};
