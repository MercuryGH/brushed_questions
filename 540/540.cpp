#include <vector>

/**
 * 有序数组中的单一元素
 * 线性异或 O(n)
 * 但是带技巧的二分法可以 O(log n)。思路是观察奇偶性反转。详见题解
 */
class Solution
{
public:
    int singleNonDuplicate(std::vector<int> &nums)
    {
        const int n = nums.size();
        int l = 0;
        int r = n - 1;
        while (true) {
            if (l > r) {
                break;
            }
            const int mid = (l + r) / 2;
            if (mid % 2 == 0) {
                if (mid + 1 < n && nums[mid] == nums[mid + 1]) {
                    l = mid + 1;
                } else {
                    r = mid;
                }
            } else {
                if (mid - 1 >= 0 && nums[mid - 1] == nums[mid]) {
                    l = mid + 1;
                } else {
                    r = mid;
                }
            }
        }
        return nums[r];
    }
};