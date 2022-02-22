#include <string>
#include <unordered_set>
#include <vector>
using std::vector, std::string;

/**
 * 给你一个字符串 s 和一个字符串列表 wordDict 作为字典。
 * 请你判断是否可以利用字典中出现的单词拼接出 s
 * 不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。
 *
 * dfs 会超时，稍微想一下可以想到记忆化搜索：
 *   -> 用一个memo[index]存当前子串 s[0:index] 是否能被wordDict拼接出来
 * 然而，想到这里，就马上应该发现它是动态规划了。
 */
class Solution
{
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {
        const int n = s.length();
        vector<bool> dp(n + 1, false);
        std::unordered_set<string> wordSet(wordDict.begin(), wordDict.end()); // 一行代码实现vector转unordered_set

        dp[0] = true;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && wordSet.find(s.substr(j, i - j)) != wordSet.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
    }
};