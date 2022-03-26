#include <stack>

/**
 * 用两个栈实现队列
 */
class MyQueue
{
    std::stack<int> s1;
    std::stack<int> s2;
    int front = 0;

public:
    MyQueue()
    {
    }

    void push(int x)
    {
        if (s1.empty())
            front = x;
        s1.push(x);
    }

    int pop()
    {
        if (empty()) {
            return -1;
        }

        if (s2.empty())
        {
            while (s1.empty() == false)
            {
                int k = s1.top();
                s1.pop();
                s2.push(k);
            }
        }
        int ret = s2.top();
        s2.pop();
        return ret;
    }

    int peek()
    {
        if (s2.empty())
        {
            return front;
        }
        return s2.top();
    }

    bool empty()
    {
        return s1.empty() && s2.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */