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
    constexpr static int INF = 0x3f3f3f3f;
    int binarySearchK(const vector<vector<int>> &dp, const int i, const int j) {
        int ans = INF;
        int l = 1;
        int r = i;
        while (true) {
            if (l > r) {
                break;
            }
            const int mid = (l + r) / 2;
            const int broken = dp[mid - 1][j - 1]; // 随 mid 单调不减
            const int notBroken = dp[i - mid][j]; // 随 mid 单调不增

            if (notBroken == broken) { // 提前找到，退出
                ans = broken;
                break;
            }

            if (notBroken > broken) { // 在左边
                ans = std::min(ans, notBroken);
                l = mid + 1;
            } else { // 在右边
                ans = std::min(ans, broken);
                r = mid - 1;
            }
        }
        return ans;
    }

    public:
    int superEggDrop(int k, int n)
    {
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
        for (int j = 0; j <= k; j++) {
            dp[0][j] = 0;
            dp[1][j] = 1;
        }
        for (int i = 1; i <= n; i++) {
            dp[i][0] = INF;
            dp[i][1] = i;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= k; j++) {
                dp[i][j] = binarySearchK(dp, i, j) + 1;
            }
        }
        return dp[n][k];
    }
};