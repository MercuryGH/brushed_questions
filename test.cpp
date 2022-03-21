#include <algorithm>
#include <ctime>
#include <cmath>
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
public:
    int lengthOfLIS(vector<int> &nums)
    {
        const int n = nums.size();
        vector<int> dp(n, 1);

        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[j] < nums[i])
                {
                    dp[i] = std::max(dp[i], dp[j] + 1);
                }
            }
            ans = std::max(ans, dp[i]);
        }

        return ans;
    }
};

int main()
{
    // int *a[10] = {nullptr};
    int a[10] = {1};

    bool same = a[0] == a[1];

    std::cout << same << "\n";

    return 0;
}