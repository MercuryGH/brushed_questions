#include <vector>
#include <algorithm>
using std::vector;

/**
 * 找出两个有序数组合并后的中位数
 */
class Solution
{
    int n, m;
    /**
     * 在 nums1[i : ], nums2[j : ] 中找 nums1, nums2 合并后的第 k (count from 1) 个元素
     */
    int findKth(const vector<int> &nums1, const vector<int> &nums2, int i, int j, int k)
    {
        if (i >= n) {
            return nums2[j + k - 1];
        }
        if (j >= m) {
            return nums1[i + k - 1];
        }
        if (k == 1) {
            return std::min(nums1[i], nums2[j]);
        }

        const int mid1 = (i + k / 2 - 1 < n) ? nums1[i + k / 2 - 1] : INT_MAX;
        const int mid2 = (j + k / 2 - 1 < m) ? nums2[j + k / 2 - 1] : INT_MAX;
        if (mid1 < mid2) {
            return findKth(nums1, nums2, i + k / 2, j, k - k / 2);
        } else {
            return findKth(nums1, nums2, i, j + k / 2, k - k / 2);
        }
    }
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        n = nums1.size();
        m = nums2.size();
        const int leftIndex = (m + n + 1) / 2;
        const int rightIndex = (m + n + 2) / 2;
        const int leftElement = findKth(nums1, nums2, 0, 0, leftIndex);
        const int rightElement = findKth(nums1, nums2, 0, 0, rightIndex);
        return (leftElement + rightElement) / 2.0;
    }
};