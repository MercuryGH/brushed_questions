#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::vector, std::string;

class Solution
{
    // nums sorted
    int twoSumClosest(const vector<int> &nums, int startIndex, int target)
    {
        const int n = nums.size();

        int l = startIndex;
        int r = n - 1;
        int minDiff = INT_MAX; // 如果答案的绝对值更小，则更新
        while (true)
        {
            if (l >= r)
            {
                break;
            }

            const int curSum = nums[l] + nums[r];
            const int diff = curSum - target; // 真正的差值
            if (std::abs(diff) < std::abs(minDiff))
            {
                minDiff = diff;
            }

            if (curSum == target)
            {
                l++;
                r--;
            }
            else if (curSum < target)
            {
                l++;
            }
            else
            {
                r--;
            }
        }
        return minDiff;
    }

public:
    int threeSumClosest(vector<int> &nums, int target)
    {
        std::sort(nums.begin(), nums.end());
        const int n = nums.size();

        int ans = 0;
        int minThreeSumDiff = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            int minDiff = twoSumClosest(nums, i + 1, target - nums[i]);
            if (std::abs(minDiff) < std::abs(minThreeSumDiff))
            {
                minThreeSumDiff = minDiff;
                ans = target + minDiff;
            }
        }
        return ans;
    }
};

int main()
{
    int a[10] = {1};

    bool same = a[0] == a[1];

    std::cout << same << "\n";

    return 0;
}