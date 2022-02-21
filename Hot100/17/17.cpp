#include <vector>
#include <string>
#include <unordered_map>

/**
 * DFS典型题，建议背诵
 */
class Solution
{
    const std::unordered_map<char, std::string> phoneDigit{
        {'2', "abc"},
        {'3', "def"},
        {'4', "ghi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"}};

    void dfs(std::vector<std::string> &combinations, const std::string &digits, int index, std::string &curCombination)
    {
        if (index == digits.length())
        {
            combinations.push_back(curCombination);
            return;
        }

        const char curDigit = digits[index];
        const std::string &letters = phoneDigit.at(curDigit);  // 取出引用的at重载更省时间
        for (const char &letter : letters)
        {
            curCombination.push_back(letter);
            dfs(combinations, digits, index + 1, curCombination);
            curCombination.pop_back();
        }
    }

public:
    std::vector<std::string> letterCombinations(std::string digits)
    {
        std::vector<std::string> ans;
        if (digits.empty() == true) {
            return ans;
        }

        std::string curCombination;
        dfs(ans, digits, 0, curCombination);
        return ans;
    }
};
