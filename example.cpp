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
public:
    int getOpPriority(std::string &word)
    {
        if (word == "+")
        {
            return 1;
        }
        if (word == "-")
        {
            return 1;
        }
        if (word == "*")
        {
            return 2;
        }
        if (word == "/")
        {
            return 2;
        }
        return 0;
    }

    void get_num_and_op(std::string &s, std::vector<std::string> &s_vec)
    {
        std::string tem_num;
        for (auto &c : s)
        { //把数和操作符存放到vector中（注意数可能多位）,如果有空格则删去
            if (c == ' ')
                continue;
            else if (c >= '0' && c <= '9')
            {
                tem_num.push_back(c);
            }
            else
            { //为操作符
                //一种特殊情况，为负号，且前面没有操作符或者为左括号
                if (!tem_num.empty())
                {
                    s_vec.push_back(tem_num);
                    tem_num.clear();
                }
                //一种特殊情况，为负号，且前面没有操作符或者为左括号
                if (c == '-' && (s_vec.empty() || s_vec.back() == "("))
                {                         //切记为空时不能访问back
                    s_vec.push_back("0"); //这样做指标且治本
                }
                //注意前面两个判断的顺序一定不能颠倒，要先入栈再判断为负号情况
                s_vec.push_back(std::string(1, c));
            }
        }
        if (!tem_num.empty())
        {
            s_vec.push_back(tem_num);
        }
    }

    // 求逆波兰式的值
    int evalRPN(std::vector<std::string> &tokens)
    {
        std::stack<std::string> stk;
        int left, right;
        for (auto &i : tokens)
        {
            if (i == "+" || i == "-" || i == "*" || i == "/")
            {
                right = std::stoi(stk.top());
                stk.pop();
                left = std::stoi(stk.top());
                if (i == "+")
                {
                    stk.top() = std::to_string(left + right);
                }
                else if (i == "-")
                {
                    stk.top() = std::to_string(left - right);
                }
                else if (i == "*")
                {
                    stk.top() = std::to_string(left * right);
                }
                else if (i == "/")
                {
                    stk.top() = std::to_string(left / right);
                }
            }
            else
            {
                stk.push(i);
            }
        }
        return std::stoi(stk.top());
    }

    //根据字符串生成逆波兰式，注意有空格
    void s_to_RPN(std::string &s, std::vector<std::string> &result)
    {
        std::vector<std::string> s_vec;
        std::stack<std::string> tem_stack;
        get_num_and_op(s, s_vec);
        for (auto &i : s_vec)
        {
            if (i == "+" || i == "-" || i == "*" || i == "/")
            { //为操作符
                if (tem_stack.empty())
                {
                    tem_stack.push(i);
                }
                else
                {
                    if (tem_stack.top() == "(")
                    {
                        tem_stack.push(i);
                    }
                    else
                    { //为操作符
                        while (!tem_stack.empty() && getOpPriority(i) <= getOpPriority(tem_stack.top()))
                        { //当前操作符优先级小于等于栈顶操作符
                            result.push_back(tem_stack.top());
                            tem_stack.pop();
                        }
                        tem_stack.push(i);
                    }
                }
            }
            else if (i == "(" || i == ")")
            {
                if (i == "(")
                {
                    tem_stack.push(i);
                }
                else
                { //为右括号
                    while (tem_stack.top() != "(")
                    { //栈顶不为左括号
                        result.push_back(tem_stack.top());
                        tem_stack.pop();
                    }
                    tem_stack.pop();
                }
            }
            else
            { //为操作数
                result.push_back(i);
            }
        }
        while (tem_stack.size() != 0)
        { //栈不为空
            result.push_back(tem_stack.top());
            tem_stack.pop();
        }
    }

    //逆波兰式就是正常式子的后缀形式
    //首先正常式子以算式作为每层的根节点，可以拆成一个二叉树，然后该二叉树的后序遍历就是逆波兰式
    int calculate(std::string s)
    {
        std::vector<std::string> result;
        s_to_RPN(s, result);
        for (const auto token : result) {
            std::cout << token << "\n";
        }
        return evalRPN(result);
    }
};

int main()
{
    Solution s;
    int ans = s.calculate("-1 - (-2)");
    std::cout << ans << "\n";
    return 0;
}