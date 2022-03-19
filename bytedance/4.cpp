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

int n;

class Solution
{
    bool check(const int initEnergy, const vector<int> &heights, const int maxHeight)
    {
        int energy = initEnergy;
        for (int i = 0; i < n; i++)
        {
            energy += (energy - heights[i]); // e = 2 * e - h_i 会指数级增长！小心溢出！
            if (energy >= maxHeight)
            {
                return true;
            }
            if (energy < 0)
            {
                return false;
            }
        }
        return true;
    }
public:
    int getMinimumInitialEnergyBin(const vector<int> &heights)
    {
        const int maxHeight = *std::max_element(heights.begin(), heights.end());
        int l = 0;
        int r = maxHeight;

        int ans = -1;
        while (true)
        {
            if (l > r)
            {
                break;
            }

            const int mid = (l + r) / 2;
            
            if (check(mid, heights, maxHeight))
            {
                r = mid - 1;
                ans = mid;
            }
            else
            {
                l = mid + 1;
            }
        }
        if (ans == -1)
        {
            std::cout << "???" << "\n";
        }
        return ans;
    }
    int getMinimumInitialEnergy(const vector<int> &heights)
    {
        double ans = 0;
        double twoPow = 2;
        for (int i = 0; i < n; i++)
        {
            ans += ((double)heights[i] / twoPow);
            twoPow *= 2;
        }

        return (int)std::ceil(ans);
    }
};

int main()
{
    // freopen("testdata.in", "r", stdin);
    std::cin >> n;
    vector<int> heights(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> heights[i];
    }

    Solution s;
    int ans = s.getMinimumInitialEnergy(heights);

    std::cout << ans << "\n";
    return 0;
}