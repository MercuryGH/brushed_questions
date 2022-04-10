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
   输出：2
 */
class Solution
{
public:
    int consecutiveNumbersSum(int target)
    {
        int ans = 0;
        for (long long l = 2; l < std::sqrt(2 * target); l++) {
            if (2 * target % l == 0) {
                const int tmp = 2 * target / l + 1 - l;
                if (tmp % 2 == 0 && tmp >= 0) {
                    const int k = tmp / 2;
                    ans++;
                    // vector<int> cur;
                    // for (int i = k; i < k + l; i++) {
                    //     cur.push_back(i);
                    // }
                    // ans.push_back(cur);
                }
            }
        }
        return ans + 1;
    }
};