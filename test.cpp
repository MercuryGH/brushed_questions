#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <ctime>
#include <iostream>
using std::vector;

/**
 * 朴素滑动窗口 O(m(n - m))
 * 一趟滑动窗口 O(n - m)
 */
class Solution
{
public:
    vector<int> goodDaysToRobBank(vector<int> &s, int t)
    {
        const int n = s.size();
        vector<int> res;
        // 两个剪枝
        if (2 * t + 1 > n)
            return res;
        if (t == 0)
        {
            for (int i = 0; i < n; i++)
                res.push_back(i);
            return res;
        }
        int cnt1, cnt2;
        cnt1 = 0; // 前面递增的个数
        cnt2 = 0; // 后面递减的个数

        for (int i = 1; i <= t; i++)
        {
            if (s[i] > s[i - 1])
                cnt1++;
        }
        for (int i = t + 1; i <= t + t; i++)
        {
            if (s[i] < s[i - 1])
                cnt2++;
        }

        for (int day = t, i = 0, j = 2 * t; ; )
        {
            if (cnt1 == 0 && cnt2 == 0)
                res.push_back(day);

            if (j + 1 == n)
                break;

            // 滑动一格
            if (s[i] < s[i + 1])
                cnt1--;
            if (s[day] < s[day + 1])
                cnt1++;
            if (s[day] > s[day + 1])
                cnt2--;
            if (s[j + 1] < s[j])
                cnt2++;
            i++;
            day++;
            j++;
        }
        return res;
    }
};

int main()
{
    Solution s;
    vector<int> nums = {6, 4, 3, 2, 7, 6, 2};

    return 0;
}