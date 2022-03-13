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
        int originPriceSum = 0;
        for (const auto &item : items) {
            originPriceSum += item.originPrice;
        }
        const int maxM = std::max(m, (originPriceSum + m) / 2);

        vector<vector<ll>> dp(n, vector<ll>(maxM + 1, 0));

        int originPriceHelper = 0;
        for (ll i = 1; i < n; i++) {
            for (ll j = 0; j <= maxM; j++) {
                const int curItemPrice = items[i].curPrice;
                if (j >= curItemPrice) {
                    const int curItemHappyValue = items[i].happyValue;
                    dp[i][j] = std::max(dp[i - 1][j], dp[i][j - curItemPrice] + curItemHappyValue);
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[n - 1][maxM];
    }
};

int main()
{
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