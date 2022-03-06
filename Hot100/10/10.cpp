#include <string>
#include <regex>
using std::string;

/**
 * 正则表达式匹配
 * 只需支持 . 和 *
 */
class Solution {
public:
    /**
     * 调库一行
     */
    bool isMatch_LIB(string s, string p) {
        return std::regex_match(s, std::regex(p, std::regex::optimize));
    }

    /**
     * 手动 DFA 解法
     * 代码很长，不写了。详见./nfa/Nfa.java
     * 基础思路与手算 Regex -> NFA 是一致的。
     * 然后
     *   在NFA里面搜索回溯（可以自己实现栈）
     *   或者把NFA转换为DFA再搜索回溯（需要耗费更多时间）
     * C++ 的 std::regex可以在构造的时候再传一个 std::regex::optimize，可以让NFA优化成DFA（但具体有没有化简状态未知）
     * 如果不传std::regex::optimize，则C++的正则引擎只会生成NFA。
     */
    bool isMatch_NFA(string s, string p) {
    }

    /**
     * DP算法
     */
    bool isMatch_DP(string s, string p) {

    }
};
