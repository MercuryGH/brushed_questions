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

/**
 * 字典序的第 k 小数字
 *
 * 输入: n = 13, k = 2
   输出: 10
   解释: 字典序的排列是 [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9]，所以第二小的数字是 10。
 */
class Solution
{
    int n;

    /**
     * @brief 获得在 prefix 下的子树的大小
     * 简单递归，会超时
     */
    int getCountUnderPrefix_BadRecursive(int prefix)
    {
        if (prefix > n)
        {
            return 0;
        }

        int cnt = 1; // 自己
        for (int i = 0; i < 10; i++)
        {
            cnt += getCountUnderPrefix_BadRecursive(prefix * 10 + i);
        }
        return cnt;
    }

    /**
     * @brief 获得在 prefix 下的子树的大小
     * 这是迭代优化的版本，O(log n) 不会超时
     * 爆 int 所以要开 long long
     */
    int getCountUnderPrefix(int prefix)
    {
        long long cnt = 0;
        for (long long cur = prefix, next = prefix + 1; cur <= n; cur *= 10, next *= 10)
        {
            cnt += std::min((long long)n + 1, next) - cur; // 闭区间，所以是 n + 1
        }
        return cnt;
    }

    bool found = false;

    /**
     * @brief 搜索十叉树找到 curRank == k 的 curNum
     * 
     * @param ans      返回值
     * @param curRank  curNum 位于 [1, n] 中的字典序（从1开始数起）
     * @param curNum   当前状态指向的数
     * @param k        目标字典序（从1开始数起）
     */
    void dfs(int &ans, int curRank, int curNum, const int k) {
        if (found) {
            return;
        }
        if (curRank == k) {
            ans = curNum;
            found = true;
            return;
        }

        for (int i = 0; i <= 9; i++) {
            if (i == 0 && curNum == 0) {
                continue;
            }
            const int child = curNum * 10 + i;
            const int prefixCnt = getCountUnderPrefix(child);
            if (curRank + prefixCnt >= k) {
                dfs(ans, curRank + 1, child, k);
                break;
            } else {
                curRank += prefixCnt;
            }
        }
    }

public:
    int findKthNumber(int n, int k)
    {
        this->n = n;
        int ans = 0;
        dfs(ans, 0, 0, k);
        return ans;
    }
};
