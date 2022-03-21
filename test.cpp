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
    bool isSquare(int num)
    {
        int sqrtNum = std::sqrt(num);
        return sqrtNum * sqrtNum == num;
    }
    bool isOdd(int num)
    {
        return num % 2 == 1;
    }
public:
    vector<vector<int>> findContinuousSequence(int target)
    {
        vector<vector<int>> ans;
        for (int k = target / 2; k >= 1; k--)
        {
            const int delta = (2 * k - 1) * (2 * k - 1) + 8 * target;
            if (isSquare(delta) == false)
            {
                continue;
            }
            const int nominator = 1 - 2 * k + std::sqrt(delta);
            if (isOdd(nominator))
            {
                continue;
            }
            const int l = nominator / 2;
            std::cout << k << " "  << l << "\n";

            const int sum = l * (2 * k + l - 1) / 2;
            std::cout << sum << "\n";
            if (sum == target)
            {
                vector<int> curAns;
                for (int i = k; i <= l; i++)
                {
                    curAns.push_back(i);
                }
                ans.push_back(curAns);
            }
        }
        return ans;
    }
};

int main()
{
    Solution s;
    s.findContinuousSequence(9);
}