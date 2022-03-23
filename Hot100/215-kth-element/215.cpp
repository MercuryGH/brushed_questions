#include <vector>
#include <ctime>
#include <algorithm>
using std::vector;

/**
 * k-th largest 经典题
 * 
 * 随机化后，平均时间复杂度为 O(n)
 */
class Solution
{
    int getPartition(vector<int> &nums, int l, int r) {
        int randomIndex = rand() % (r - l + 1) + l;
        std::swap(nums[randomIndex], nums[l]);

        const int pivot = nums[l];
        int ptr = l;
        for (int i = l + 1; i <= r; i++) {
            if (nums[i] <= pivot) {
                ptr++;
                std::swap(nums[ptr], nums[i]);
            }
        }
        std::swap(nums[ptr], nums[l]);
        return ptr;
    }

    /**
     * 在只讨论 nums[l:r] 时，获取最终排序结果中下标为 k 的元素
     */
    int quickSortSelect(vector<int> &nums, int l, int r, int k) {
        int partition = getPartition(nums, l, r);
        if (partition == k) {
            return nums[k];
        }

        if (partition < k) {
            return quickSortSelect(nums, partition + 1, r, k);
        }
        return quickSortSelect(nums, l, partition - 1, k);
    }
public:
    int findKthLargest(vector<int> &nums, int k)
    {
        srand(time(0));
        const int n = nums.size();
        // 最终排序结果中的 nums[n - k] == 第 k 大元素 ( k ∈ [1, n] )
        return quickSortSelect(nums, 0, n - 1, n - k);
    }
};