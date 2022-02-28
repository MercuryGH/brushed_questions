#include <vector>
#include <algorithm>
using std::vector;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        const int n = prices.size();

        int leftMin = INT_MAX;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            const int curNum = prices[i];
            if (curNum == leftMin) {
                continue;
            }

            ans = std::max(ans, curNum - leftMin);
            leftMin = std::min(leftMin, curNum);
        }
        return ans;
    }
};