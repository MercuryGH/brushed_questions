#include <string>
#include <vector>
using std::vector, std::string;

/**
 * 括号生成，建议背诵
 * 这里等价转换成了棋盘搜索法，非常直观
 * 
 * 本题背景为卡特兰数，有迭代的利用卡特兰数递推公式的解法
 */
class Solution
{
    int n;
    const int dirs[2][2] = {{1, 0}, {0, 1}};

    bool outOfBound(int x, int y) {
        return x < 0 || x > n || y < 0 || y > n || y >= x + 1;
    }

    void dfs(vector<string> &combinations, string &curCombination, int x, int y)
    {
        if (x == n && y == n) {
            combinations.push_back(curCombination);
            return;
        }

        for (const auto &dir : dirs) {
            const int nx = x + dir[0];
            const int ny = y + dir[1];
            if (outOfBound(nx, ny) == false) {
                if (nx - x == 1) {
                    curCombination.push_back('(');
                } else {
                    curCombination.push_back(')');
                }
                dfs(combinations, curCombination, nx, ny);
                curCombination.pop_back();
            }
        }
    }

public:
    std::vector<std::string> generateParenthesis(int n)
    {
        this->n = n;
        vector<string> ans;
        string cur;
        dfs(ans, cur, 0, 0);
        return ans;
    }
};
