#include <vector>
#include <algorithm>

class Solution
{
public:
    int numberOfWeakCharacters(std::vector<std::vector<int>> &properties)
    {
        const auto cmp = [](const auto &x, const auto &y)
        {
            // 攻击力高的在前面
            // 攻击力相同，防御力低的在前面
            return x[0] > y[0] || (x[0] == y[0] && x[1] < y[1]);
        };
        std::sort(properties.begin(), properties.end(), cmp);

        int maxDef = -1;
        int ans = 0;
        for (const auto &property : properties)
        {
            const int curAtk = property[0];
            const int curDef = property[1];
            if (curDef < maxDef)
            {
                ans++;
            }
            else
            {
                maxDef = curDef;
            }
        }
        return ans;
    }
};
