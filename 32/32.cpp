#include <vector>
#include <algorithm>
#include <stack>
#include <string>
using std::vector, std::string;

/**
 * 最长有效括号序列：
 * 思想：先用栈扫一遍序列，遇到多余的右括号就标记，或者遇到最后剩余的左括号也标记。
 * 然后，找标记序列连续的 0 的最大长度即可。
 * 
 * 例如: ")()((())"的mark为[1, 0, 0, 1, 0, 0, 0, 0]，答案为 4
 */
class Solution {
public:
    int longestValidParentheses(string s) {
        const int n = s.length();
        std::stack<int> stk;
        vector<bool> mark(n, false);
        
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                stk.push(i);
            } else if (s[i] == ')') {
                if (stk.empty() == true) {
                    mark[i] = true;
                } else {
                    stk.pop();
                }
            }
        }
        while (stk.empty() == false) {
            mark[stk.top()] = true;
            stk.pop();
        }

        int ans = 0;
        int maxLen = 0;
        for (int i = 0; i < n; i++) {
            if (mark[i] == false) {
                maxLen++; // 连续的0
            } else { // 断了
                ans = std::max(ans, maxLen); // 可能更新答案
                maxLen = 0; // 重置连续的0的长度
            }
        }
        ans = std::max(ans, maxLen); // 可能更新答案
        return ans;
    }
};