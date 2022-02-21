#include <vector>
#include <algorithm>

/**
 * 移动零
 * 有开辟额外空间的 O(n) Naive 算法
 *
 * 双指针法 不需要开辟额外空间：
 * 维护一个左指针，一个右指针：左指针左边均为非零数；右指针左边直到左指针处均为零。
 * 或者直接说：维护一个 pivot （类似于快速排序），其左边都不是0，右边都是0
 */
class Solution
{
public:
    void moveZeroes(std::vector<int> &nums)
    {
        const int n = nums.size();

        int pivot = 0;  // a[pivot] 本身是或不是0不确定，但其左边都不是0，右边都是0
        for (int i = 0; i < n; i++) {
            if (nums[i] != 0) {  // 发现非零元素
                std::swap(nums[i], nums[pivot]);  // 为了保证 pivot 的性质
                pivot++;  // pivot必须后退一步
            }
        }
    }
};