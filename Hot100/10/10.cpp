#include <string>
#include <regex>
#include <unordered_set>
using std::string;

/**
 * 正则表达式匹配
 * 只需支持 . 和 *
 */
class Solution
{
public:
    /**
     * 调库一行
     */
    bool isMatch_LIB(string s, string p)
    {
        return std::regex_match(s, std::regex(p, std::regex::optimize));
    }

    /**
     * 手动 FA 解法
     * 代码很长，不写了。详见./nfa/Nfa.java
     * 基础思路与手算 Regex -> NFA 是一致的。
     * 然后
     *   在NFA里面搜索回溯（可以自己实现栈）
     *   或者把NFA转换为DFA再搜索回溯（需要耗费更多时间）
     * C++ 的 std::regex可以在构造的时候再传一个 std::regex::optimize，可以让NFA优化成DFA（但具体有没有化简状态未知）
     * 如果不传std::regex::optimize，则C++的正则引擎只会生成NFA。
     */

    /**
     * 模拟 NFA
     * 每个状态用 int 来唯一确定
     * s: 待匹配的字符串， p: 正则表达式
     */
    bool isMatch_NFA(string s, string p)
    {
        const int n = s.length();
        const int m = p.length();
        std::unordered_set<int> curStates;

        const auto add = [&](std::unordered_set<int> &states, int state)
        {
            states.insert(state);
            while (state + 1 < m && p[state + 1] == '*') // 这里的判断 <m 只是为了防止越界
            {
                state += 2; // 指针向右移动两格（考虑空转移）
                states.insert(state);
            }
        };
        add(curStates, 0);

        bool matched = false;
        for (const char c : s)
        {
            matched = false;
            std::unordered_set<int> nextStates;
            for (const auto &curState : curStates)
            {
                if (p[curState] == c || p[curState] == '.')
                {
                    if (curState + 1 < m && p[curState + 1] == '*') // 空转移
                    {
                        add(nextStates, curState);
                    }
                    else // 非空转移
                    {
                        add(nextStates, curState + 1);
                    }
                }
            }
            if (nextStates.find(m) != nextStates.end())
            {
                matched = true;
            }
            curStates = nextStates;
        }
        return matched;
    }

    /**
     * DP算法
     *
     * 太复杂一点也不优雅，不写了
     */
    bool isMatch_DP(string s, string p)
    {
    }
};
