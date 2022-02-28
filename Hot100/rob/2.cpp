#include <algorithm>
#include <iostream>
#include <vector>
using std::vector;

class Solution
{
    int robSub(std::vector<int> &nums)
    {
        const int n = nums.size();
        if (n == 0)
        {
            return 0;
        }
        if (n == 1)
        {
            return nums[0];
        }

        int first = nums[0];
        int second = std::max(nums[0], nums[1]);
        for (int i = 2; i < n; i++)
        {
            int temp = second;
            second = std::max(first + nums[i], second);
            first = temp;
        }
        return second;
    }

public:
    int rob(vector<int> &nums)
    {
        const int n = nums.size();
        if (n == 1)
        {
            return nums[0];
        }

        vector<int> tmp(n - 1);
        std::move(nums.begin(), nums.end() - 1, tmp.begin());
        const int res1 = robSub(tmp);
        std::move(nums.begin() + 1, nums.end(), tmp.begin());
        const int res2 = robSub(tmp);
        return std::max(res1, res2);
    }
};