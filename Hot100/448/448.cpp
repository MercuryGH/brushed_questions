#include <vector>

/**
 * 给出一个元素只在 [1, n] 范围内的大小为 n 的数组，求 [1, n] 范围内没有出现的所有数字的集合
 * 哈希表需要额外空间
 * 本题可用原地哈希的方式压榨空间，但本方法的技巧性很高，且有溢出风险，不推荐学习
 */
class Solution
{
public:
    std::vector<int> findDisappearedNumbers(std::vector<int> &nums)
    {
        const int n = nums.size();
        for (const auto num : nums)
        {
            int x = (num - 1) % n;
            nums[x] += n;
        }

        std::vector<int> ret;
        for (int i = 0; i < n; i++)
        {
            if (nums[i] <= n)
            {
                ret.push_back(i + 1);
            }
        }
        return ret;
    }
};