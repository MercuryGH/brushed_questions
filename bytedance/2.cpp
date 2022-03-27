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

int n, m;

class Solution
{
    bool check(const vector<int> &orders, const int waiters, const int time)
    {
        vector<int> tmpOrders(orders);
        int farthestOrderIndex = n - 1;
        for (int i = 0; i < waiters; i++)
        {
            const int moveTime = farthestOrderIndex + 1; // 移动过去
            int remainedTime = time - moveTime;
            while (true)
            {
                const int needTime = tmpOrders[farthestOrderIndex]; // 需要这么多时间服务
                if (remainedTime >= needTime)
                {
                    farthestOrderIndex--;
                    if (farthestOrderIndex == -1) {
                        return true;
                    }
                    remainedTime -= needTime;
                }
                else
                {
                    tmpOrders[farthestOrderIndex] -= remainedTime;
                    break;
                }
            }
        }
        return false;
    }

public:
    int minimumTimeToFinishOrders(vector<int> &orders, const int waiters)
    {
        int l = n + 1;
        int r = 1e7 + 7;
        int ans = l;
        while (true) {
            if (l > r) {
                break;
            }

            const int mid = (l + r) / 2;
            if (check(orders, waiters, mid)) {
                r = mid - 1;
                ans = mid;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }
};

int main()
{
    string str;
    std::getline(std::cin, str);
    freopen("testdata.in", "r", stdin);
    
    std::cin >> m >> n;
    vector<int> orders(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> orders[i];
    }

    Solution s;
    std::cout << s.minimumTimeToFinishOrders(orders, m) << "\n";

    return 0;
}