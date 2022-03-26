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
    static constexpr int INF = 0x3f3f3f3f;

public:
    int jump(vector<int> &nums)
    {
        const int n = nums.size();
        vector<int> dp(n, INF);
        dp[0] = 0;

        int maxReach = 0;
        for (int i = 0; i < n; i++)
        {
            const int curReach = std::min(n - 1, i + nums[i]);
            if (curReach > maxReach)
            {
                for (int j = maxReach + 1; j <= curReach; j++)
                {
                    dp[j] = dp[i] + 1;
                }
                maxReach = curReach;
            }
        }
        return dp[n - 1];
    }
};