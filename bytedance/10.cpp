#include <algorithm>
#include <ctime>
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

vector<string> readArray(string inputStr)
{
    vector<string> ans;
    for (int i = 1, j = 1; j < inputStr.size(); j++)
    {
        if (inputStr[j] == ',' || inputStr[j] == ']')
        {
            string num = inputStr.substr(i, j - i);
            ans.push_back(num);
            i = j + 1;
        }
    }
    return ans;
}

/**
 * 给定一组非负整数，重新排列它们的顺序使之组成一个最大的整数。
 * 输入：[3, 30, 34, 5, 9]
 * 输出：9534330
 * 
 * 思路：贪心，暴力用自定义 cmp 排序即可
 * 实际需要证明该关系具有传递性
 */
class Solution
{
public:
    string getLargestLexicographicalOrderCombination(vector<string> numStrs)
    {
        const auto cmp = [](string a, string b)
        {
            return a + b > b + a;
        };
        std::sort(numStrs.begin(), numStrs.end(), cmp);

        string ans;
        for (const auto &numStr : numStrs)
        {
            ans += numStr;
        }
        return ans;
    }
};

int main()
{
    string inputStr;
    std::cin >> inputStr;
    vector<string> numStrs = readArray(inputStr);

    Solution s;
    string ans = s.getLargestLexicographicalOrderCombination(numStrs);
    std::cout << ans << "\n";

    return 0;
}