#include <algorithm>
#include <vector>
#include <stack>
using std::vector;

class Solution
{
public:
    vector<int> dailyTemperatures(vector<int> &temperatures)
    {
        const int n = temperatures.size();
        if (n == 0) {
            return {};
        }
        if (n == 1) {
            return {0};
        }

        std::stack<std::pair<int, int>> minStack;
        vector<int> ans(n, 0);
        minStack.push({0, temperatures[0]});
        for (int i = 1; i < n; i++) {
            const int curTemperature = temperatures[i];
            while (true) {
                if (minStack.empty() == true) {
                    break;
                }
                const auto [topIndex, topElement] = minStack.top();
                if (curTemperature > topElement) {
                    minStack.pop();
                    ans[topIndex] = i - topIndex;
                } else {
                    break;
                }
            }
            minStack.push({i, curTemperature});
        }
        return ans;
    }
};