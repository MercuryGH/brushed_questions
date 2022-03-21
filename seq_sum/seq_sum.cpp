#include <algorithm>
#include <numeric>
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

/**
 * 输入一个正整数 target ，输出所有和为 target 的连续正整数序列（至少含有两个数）。
 *
 * 输入：target = 9
   输出：[[2,3,4],[4,5]]
 */
class Solution
{
    bool isSquare(long long num)
    {
        long long sqrtNum = std::sqrt(num);
        return sqrtNum * sqrtNum == num;
    }
    bool isOdd(long long num)
    {
        return num % 2 == 1;
    }
public:
    vector<vector<int>> findContinuousSequence(int target)
    {
        vector<vector<int>> ans;
        for (long long k = 1; k <= target / 2; k++)
        {
            const long long delta = (2 * k - 1) * (2 * k - 1) + 8 * target;
            if (isSquare(delta) == false)
            {
                continue;
            }
            const long long nominator = 1 - 2 * k + std::sqrt(delta);
            if (isOdd(nominator))
            {
                continue;
            }
            const long long l = nominator / 2;

            const int sum = l * (2 * k + l - 1) / 2;
            if (sum == target)
            {
                vector<int> curAns;
                for (int i = k; i < k + l; i++)
                {
                    curAns.push_back(i);
                }
                ans.push_back(curAns);
            }
        }
        return ans;
    }
};