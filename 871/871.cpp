#include <algorithm>
#include <ctime>
#include <cmath>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <stack>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::vector, std::string;

/**
 *  最低加油次数
 *  超经典的贪心，但难度不小
 */
class Solution
{
    using ll = long long;

    struct GasStation {
        int pos;
        int gas;
        GasStation(int pos, int gas): pos(pos), gas(gas) {}
    };
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>> &stations)
    {
        const int n = stations.size();
        vector<GasStation> gasStations;
        gasStations.emplace_back(-1, -1); // pivot，因为 [0] 不必使用
        for (const auto &station : stations) {
            gasStations.emplace_back(station[0], station[1]);
        }

        vector<vector<ll>> dp(n + 1, vector<ll>(n + 1));
        dp[0][0] = startFuel;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= i; j++) {
                int tmp1 = -1, tmp2 = -1;
                if (dp[i - 1][j] >= gasStations[i].pos) {
                    tmp1 = dp[i - 1][j];
                }
                if (j >= 1 && dp[i - 1][j - 1] >= gasStations[i].pos) {
                    tmp2 = dp[i - 1][j - 1] + gasStations[i].gas;
                }
                dp[i][j] = std::max(tmp1, tmp2);
            }
        }
        
        for (int j = 0; j <= n; j++) {
            if (dp[n][j] >= target) {
                return j;
            }
        }
        return -1;
    }
};