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
            for (int j = maxReach; j <= i + nums[i]; j++)
            {
                dp[j] = dp[i] + 1;
            }
            maxReach = std::max(maxReach, i + nums[i]);
        }
        return dp[n - 1];
    }
};

int main()
{
    int a = 2;
    std::cout << (!a) << "\n";
    return 0;
}