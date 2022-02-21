#include <stack>
#include <algorithm>

/**
 * 最小栈，能满足栈的性质并且还能在常数时间复杂度内检索到最小元素
 * 因为要满足栈的性质，所以还不能用堆来做
 * 
 * 最好的解题思路，就是以空间换时间
 * 每次新元素 x 入栈的时候保存一个元组：（当前值 x，入栈后的栈内最小值）。
 * 维护这个“栈内最小值”即可
 */
class MinStack {
    std::stack<std::pair<int, int>> s;
public:
    MinStack() {
    }
    
    void push(int val) {
        if (s.empty() == true) {
            s.push({val, val});
        } else {
            const int nextMin = std::min(val, s.top().second);
            s.push({val, nextMin});
        }
    }
    
    void pop() {
        s.pop();  // 不需更新栈内最小值，因为状态变化是单向的
    }
    
    int top() {
        return s.top().first;
    }
    
    int getMin() {
        return s.top().second;
    }
};