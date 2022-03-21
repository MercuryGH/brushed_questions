#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
using std::string;

/**
 * 字符串转为整型
 *
 * DFA 例题
 */
class Solution
{
    struct Dfa
    {
        enum State
        {
            START,
            SIGN,
            NUMBER,
            END
        };
        const std::unordered_map<State, std::vector<State>> table = {
            // 始态在 空格、符号、数字和其他下的转移态
            {START, {START, SIGN, NUMBER, END}},
            {SIGN, {END, END, NUMBER, END}},
            {NUMBER, {END, END, NUMBER, END}},
            {END, {END, END, END, END}}};

        static int getNextStateIndex(char c)
        {
            if (isspace(c))
            {
                return 0;
            }
            if (c == '+' || c == '-')
            {
                return 1;
            }
            if (isdigit(c))
            {
                return 2;
            }
            return 3;
        }

        int sign = 1;
        long long ans = 0;
        State curState = START;
        void getChar(char c)
        {
            const State nextState = table.at(curState).at(getNextStateIndex(c));
            switch (nextState)
            {
            case NUMBER:
            {
                ans *= 10;
                ans += c - '0';
                if (sign == 1)
                {
                    ans = std::min(ans, (long long)INT_MAX); // 溢出需要截断
                }
                else
                {                                             // 负数，注意 ans 保存的是绝对值
                    ans = std::min(ans, -(long long)INT_MIN); // 同上
                }
                break;
            }
            case SIGN:
            {
                if (c == '+')
                {
                    sign = 1;
                }
                else
                {
                    sign = -1;
                }
                break;
            }
            default:
                break;
            }
            curState = nextState;
        }
    };

public:
    int myAtoi(string s)
    {
        Dfa dfa;
        for (const char c : s)
        {
            dfa.getChar(c);
        }
        return dfa.sign * dfa.ans;
    }
};