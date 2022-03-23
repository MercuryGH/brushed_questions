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
     * 获取 prefix 下的子树的大小
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

    // 迭代优化，O(log n) 不会超时
    // 爆 int 所以要开 long long
    int getCountUnderPrefix(int prefix)
    {
        long long cnt = 0;
        for (long long cur = prefix, next = prefix + 1; cur <= n; cur *= 10, next *= 10)
        {
            cnt += std::min((long long)n + 1, next) - cur; // 闭区间，所以是 n + 1
        }
        return cnt;
    }

public:
    int findKthNumber(int n, int k)
    {
        this->n = n;

        int ptr = 1; // 当前所在的数是字典序第 ptr 小的数
        int prefix = 1;
        while (true)
        {
            if (ptr == k) // 依照下面的算法，不可能出现 ptr > k 的情况
            {
                break;
            }

            int cnt = getCountUnderPrefix(prefix);
            if (ptr + cnt > k) // 第 k 个数在 prefix 下
            {
                prefix *= 10; // 往下搜
                ptr++;
            }
            else // 不在当前前缀下
            {
                prefix++; // 往右搜
                ptr += cnt;
            }
        }
        return prefix;
    }
};