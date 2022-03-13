#include <algorithm>
#include <ctime>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <memory>
using std::vector, std::string;

using ll = long long;
int n, m;

struct Item
{
    int originPrice;
    int curPrice;
    int happyValue;
    Item() {}
    Item(int originPrice, int curPrice, int happyValue) : originPrice(originPrice), curPrice(curPrice), happyValue(happyValue) {}
};

class Solution
{
public:
    ll getMaximumHappyValue(const vector<Item> &items)
    {
        ll freeHappyValue = 0;
        vector<int> weights = {0}; // 下标从 1 开始
        vector<int> values = {0};  // 下标从 1 开始
        for (int i = 0; i < n; i++)
        {
            const Item &item = items[i];
            const int weight = item.curPrice - (item.originPrice - item.curPrice);
            if (weight <= 0)
            { // free item
                m -= weight;
                freeHappyValue += item.happyValue;
            }
            else
            {
                weights.push_back(weight);
                values.push_back(item.happyValue);
            }
        }

        const int n = weights.size() - 1; // 注意下标从 1 开始！！
        vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, 0));
        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j <= m; j++)
            {
                if (j >= weights[i])
                {
                    dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - weights[i]] + values[i]);
                }
                else
                {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }

        return dp[n][m] + freeHappyValue;
    }
};

int main()
{
    // freopen("testdata.in", "r", stdin);
    std::cin >> n >> m;
    vector<Item> items(n);
    for (int i = 0; i < n; i++)
    {
        int originPrice, curPrice, happyValue;
        std::cin >> originPrice >> curPrice >> happyValue;
        items[i] = Item(originPrice, curPrice, happyValue);
    }

    Solution s;
    const ll ans = s.getMaximumHappyValue(items);

    std::cout << ans << "\n";

    return 0;
}