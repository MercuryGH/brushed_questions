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

/**
 * 分发糖果
 * 单向遍历的贪心很容易错（虽然也有空间O(1)的高技巧做法）。必须双向遍历
 */
class Solution
{
public:
    int candy(vector<int> &ratings)
    {
        const int n = ratings.size();

        vector<int> lRScan(n);
        lRScan[0] = 0;
        for (int i = 1; i < n; i++)
        {
            if (ratings[i] > ratings[i - 1])
            {
                lRScan[i] = lRScan[i - 1] + 1;
            }
        }

        vector<int> rLScan(n);
        rLScan[n - 1] = 0;
        for (int i = n - 2; i >= 0; i--)
        {
            if (ratings[i] > ratings[i + 1])
            {
                rLScan[i] = rLScan[i + 1] + 1;
            }
        }

        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            ans += std::max(lRScan[i], rLScan[i]);
        }
        return ans + n;
    }
};