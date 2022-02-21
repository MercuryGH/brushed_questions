#include <vector>
using std::vector;

/**
 * 将正整数分解成若干正偶整数之和，每个正偶整数只能用一次
 * 返回使用的正偶整数最多的方案之一
 * 
 * 贪心策略：就硬拿 2i (i = 1 to n) 来拆，如果拆完后的结果与之前有重复，就特殊处理
 */
class Solution {
public:
    vector<long long> maximumEvenSplit(long long finalSum) {
        if (finalSum % 2 == 1) {
            return {};
        }

        vector<long long> ans;
        long long sum = 0;
        for (long long i = 2; ; i += 2) {
            long long prevSum = sum + i;
            if (prevSum + i + 2 > finalSum) {
                if (sum == finalSum) {
                    ans.push_back(i);
                } else {
                    ans.push_back(finalSum - sum);
                }
                break;
            }
            ans.push_back(i);
            sum = prevSum;
        }
        return ans;
    }
};
