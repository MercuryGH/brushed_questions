#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::vector, std::string;

class Solution
{
    // 动态规划 O(nk)，超时
    /*
    int dpAt(string s, int k, char c)
    {
        for (int i = 2; i <= n; i++)
        {
            for (int j = 0; j <= k; j++)
            {
                if (s[i] == c)
                {
                    dp[i][j] = dp[i - 1][j] + 1;
                }
                else if (j > 0)
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                ans = std::max(ans, dp[i][j]);
            }
        }
        return ans;
    }
    */
    int longestCs(string answerKey, int k, char c)
    {
        const int n = answerKey.size();
        int l = 0;
        int r = 0;
        int ans = 0;
        int windowZeroNum = 0;
        while (true)
        {
            if (r >= n)
            {
                break;
            }
            if (answerKey[r] == c)
            {
                windowZeroNum++;
            }
            if (windowZeroNum > k)
            {
                while (true)
                {
                    if (answerKey[l] == c)
                    {
                        windowZeroNum--;
                    }
                    l++;
                    if (windowZeroNum == k)
                    {
                        break;
                    }
                }
            }

            ans = std::max(ans, r - l + 1);
            r++;
        }
        return ans;
    }

public:
    int maxConsecutiveAnswers(string answerKey, int k)
    {
        return std::max(longestCs(answerKey, k, 'T'), longestCs(answerKey, k, 'F'));
    }
};

int main()
{
    bool b = false;
    vector<bool> vs = {b, b, b, b, b, b};
    vector<int> vv = {b, b, b, b, b, b};
    std::cout << sizeof(vs) << " " << sizeof(vv) << "\n";

    return 0;
}