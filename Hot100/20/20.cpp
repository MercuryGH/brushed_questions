#include <string>
#include <stack>
#include <unordered_map>

/**
 * 括号匹配题目，有三种括号
 * 让右括号去找栈顶的左括号匹配
 */
class Solution
{
public:
    bool isBalance(std::string s)
    {
        int n = s.size();
        if (n % 2 == 1)  // 可以提前结束
        {
            return false;
        }

        std::unordered_map<char, char> pairs = {
            {')', '('},
            {']', '['},
            {'}', '{'}};  
        // (unordered_)map 不能用 constexpr 修饰，但有一个实验性的 frozen::map
        // (unordered_)map 如果用 const 修饰，则不能用 [] 运算符（因为可能修改本身）。可以用 std::unordered_map.at(digit) 代替
        std::stack<char> stk;
        for (const char ch : s)
        {
            // key = ch, value = pairs[ch]
            if (pairs.find(ch) != pairs.end())  // 是右括号
            {
                if (stk.empty() == true || stk.top() != pairs[ch])
                {
                    return false;
                }
                stk.pop();
            }
            else  // 是左括号
            {
                stk.push(ch);
            }
        }
        return stk.empty();
    }
};
