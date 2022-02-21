#include <vector>
#include <string>

/**
 * 括号生成，建议背诵DFS
 * 本题背景为卡特兰数，有迭代的利用卡特兰数递推公式的解法
 */
class Solution {
    void dfs(std::vector<std::string> &combinations, std::string &curCombination, int open, int close, int n) {
        if (open + close == n * 2) {
            combinations.push_back(curCombination);
            return;
        }

        if (open < n) {
            curCombination.push_back('(');
            dfs(combinations, curCombination, open + 1, close, n);
            curCombination.pop_back();
        }
        if (close < open) {
            curCombination.push_back(')');
            dfs(combinations, curCombination, open, close + 1, n);
            curCombination.pop_back();
        }
    }
public:
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> ans;
        std::string cur;
        dfs(ans, cur, 0, 0, n);
        return ans;
    }
};
