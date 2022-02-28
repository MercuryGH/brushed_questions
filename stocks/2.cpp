#include <vector>
#include <algorithm>
using std::vector;

class Solution {
public:
    int maxProfit(vector<int>& prices) {   
        const int n = prices.size();

        int ans = 0;
        for (int i = 1; i < n; ++i) {
            ans += std::max(0, prices[i] - prices[i - 1]);
        }
        return ans;
    }
};