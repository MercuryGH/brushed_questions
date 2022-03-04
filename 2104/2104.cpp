#include <vector>
#include <algorithm>
using std::vector;

/**
 * 子数组范围和
 * 计算 nums 中所有子数组的极差之和
 */
class Solution
{
public:
    long long subArrayRanges(vector<int> &nums)
    {
        const int n = nums.size();

        long long ans = 0;
        int f = 0;
        int g = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = i; j < n; j++)
            {
                if (j == i)
                {
                    f = nums[i];
                    g = nums[i];
                }
                else
                {
                    f = std::max(f, nums[j]);
                    g = std::min(g, nums[j]);
                    ans += (f - g);
                }
            }
        }
        return ans;
    }
};