#include <vector>
#include <algorithm>
#include <stack>
#include <string>
using std::vector, std::string;

/**
 * 给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数  。
    你可以对一个单词进行如下三种操作：
      插入一个字符
      删除一个字符
      替换一个字符
*/
class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        const int n = word1.length();
        const int m = word2.length();
        if (n == 0 || m == 0) {
            return n + m;
        }

        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        for (int i = 0; i <= n; i++) {
            dp[i][0] = i;
        }
        for (int j = 0; j <= m; j++) {
            dp[0][j] = j;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                const int tmp1 = dp[i - 1][j] + 1;
                const int tmp2 = dp[i][j - 1] + 1;
                int tmp3 = dp[i - 1][j - 1];
                if (word1[i - 1] != word2[j - 1]) { // 注意dp数组与字符串数组有一位偏移，所以这里要 -1
                    tmp3++;
                }
                dp[i][j] = std::min(tmp1, std::min(tmp2, tmp3));
            }
        }
        return dp[n][m];
    }
};