#include <vector>

/**
 * next permutation 模板题
    1. 从后向前查找第一个相邻升序的元素对 (i,j), j = i + 1，满足 A[i] < A[j]。此时 [j,end) 必然是降序
    2. 在 [j,end) 从后向前查找第一个满足 A[i] < A[k] 的 k。A[i]、A[k] 分别就是上文所说的「小数」、「大数」
    3. 将 A[i] 与 A[k] 交换
    4. 可以断定这时 [j,end) 必然是降序，逆置 [j,end)，使其升序
    5. 如果在步骤 1 找不到符合的相邻元素对，说明当前 [begin,end) 为一个降序顺序，则直接跳到步骤 4
 */
class Solution
{
public:
    void nextPermutation(std::vector<int> &nums)
    {
        const int n = nums.size();
        int firstIncPairIndex = -1;
        for (int i = n - 2; i >= 0; i--) // 从后往前找到第一个相邻升序对
        {
            if (nums[i] < nums[i + 1])
            {
                firstIncPairIndex = i;
                break;
            }
        }

        if (firstIncPairIndex == -1)
        { // 特殊情况，整个 nums 都是降序的
            std::reverse(nums.begin(), nums.end());
            return;
        }

        for (int i = n - 1; i >= firstIncPairIndex + 1; i--)
        { // 从后往前[i+1,end)找第一个大于a[i+1]的值
            if (nums[firstIncPairIndex] < nums[i])
            {
                std::swap(nums[firstIncPairIndex], nums[i]);
                std::reverse(nums.begin() + firstIncPairIndex + 1, nums.end());
                return;
            }
        }
    }
    /* STL一行
    void nextPermutation(vector<int>& nums) {
        next_permutation(nums.begin(), nums.end());
    }
    */
};
