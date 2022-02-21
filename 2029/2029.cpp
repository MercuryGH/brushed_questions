/**
 * 博弈论题目
 * 重点：结合状态转移图思考
 * 其实我无法理解类型为 0 的石子个数为奇数的情况。偶数倒是挺简单的
 */
#include <vector>
#include <cmath>

class Solution
{
public:
    bool stoneGameIX(std::vector<int> &stones)
    {
        int nMod[3] = {0};
        for (int val : stones)
        {
            int modular = val % 3;
            nMod[modular]++;
        }
        if (nMod[0] % 2 == 0)
        {
            return nMod[1] >= 1 && nMod[2] >= 1;
        }
        return std::abs(nMod[1] - nMod[2]) > 2;
    }
};