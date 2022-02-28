#include <vector>
#include <algorithm>
using std::vector, std::max;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        const int n = prices.size();
        vector<vector<int>> buy(n, vector<int>(2));
        vector<vector<int>> sell(n, vector<int>(2));
        buy[0][0] = -prices[0];
        buy[0][1] = -prices[0];
        for (int i = 1; i < n; i++) {
            buy[i][0] = max(buy[i - 1][0], -prices[i]);
            sell[i][0] = max(sell[i - 1][0], buy[i - 1][0] + prices[i]);
            buy[i][1] = max(buy[i - 1][1], sell[i][0] - prices[i]);
            sell[i][1] = max(sell[i - 1][1], buy[i - 1][1] + prices[i]);
        }
        return max(0, max(sell[n - 1][0], sell[n - 1][1]));
    }
};

