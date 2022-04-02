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

struct Node
{
    char val;
    Node *left;
    Node *right;
    Node() : val(' '), left(nullptr), right(nullptr) {}
    Node(char x) : val(x), left(nullptr), right(nullptr) {}
    Node(char x, Node *left, Node *right) : val(x), left(left), right(right) {}
};

struct Operator;
struct Number;
struct Bracket;

struct Token
{
    virtual void performInConvertion(vector<Token *> &result, std::stack<Operator *> &s) = 0;
    virtual void performInEvaluaion(std::stack<Number *> &s) = 0;
    virtual void performInAstConstruction(std::stack<Node *> &s) = 0;
    virtual void print() const = 0;
};

struct Number : Token
{
    int value;
    Number(int value) : value(value) {}

    // 数，直接输出
    virtual void performInConvertion(vector<Token *> &result, std::stack<Operator *> &s) override
    {
        result.push_back(this);
    }
    virtual void performInEvaluaion(std::stack<Number *> &s) override
    {
        s.push(this);
    }
    virtual void performInAstConstruction(std::stack<Node *> &s) override
    {
        s.push(new Node(value + '0'));
    }
    virtual void print() const override
    {
        std::cout << value << "\n";
    }
};

struct Operator : Token
{
    char op;
    Operator(char op) : op(op) {}

    // 维护单调栈
    // 栈顶的运算符优先级高
    virtual void performInConvertion(vector<Token *> &result, std::stack<Operator *> &s) override
    {
        while (true)
        {
            if (s.empty() == true)
            {
                break;
            }
            Operator *top = s.top();
            if (top->op == '(') // 与 s.empty() 等价
            {
                break;
            }
            if (top->getPriority() < this->getPriority())
            {
                break;
            }

            s.pop();
            result.push_back(top);
        }
        s.push(this);
    }
    virtual void performInEvaluaion(std::stack<Number *> &s) override
    {
        Number *a1 = s.top();
        s.pop();
        if (s.empty() == true && op == '-') // 一操作数。实际上根本不可能走这一分支
        {
            a1->value = -a1->value;
            s.push(a1);
        }
        else // 二操作数
        // 实际上，以下操作都可以简化为只 pop 一次，效率更高
        {
            Number *a2 = s.top();
            s.pop();

            Number *res = nullptr;
            switch (op)
            {
            case '+':
                res = new Number(a2->value + a1->value);
                break;
            case '-':
                res = new Number(a2->value - a1->value);
                break;
            case '*':
                res = new Number(a2->value * a1->value);
                break;
            case '/':
                res = new Number(a2->value / a1->value);
                break;
            default:
                break;
            }
            delete a1;
            delete a2;
            s.push(res);
        }
    }
    virtual void performInAstConstruction(std::stack<Node *> &s) override
    {
        Node *a1 = s.top();
        s.pop();
        Node *a2 = s.top();
        s.pop();
        Node *root = new Node(op, a2, a1);
        s.push(root);
    }
    virtual void print() const override
    {
        std::cout << op << "\n";
    }
    int getPriority() const
    {
        if (op == '+' || op == '-')
        {
            return 1;
        }
        else if (op == '*' || op == '/')
        {
            return 2;
        }
        return 0;
    }
};

struct Bracket : Operator
{
    Bracket(char op) : Operator(op) {}

    virtual void performInConvertion(vector<Token *> &result, std::stack<Operator *> &s) override
    {
        if (op == '(')
        {
            s.push(this);
        }
        else if (op == ')')
        {
            // 右括号，pop直到 ( 被弹出
            // 如果栈为空，也没有 (，说明括号不匹配（未处理此情况）
            while (s.empty() == false)
            {
                Operator *top = s.top();
                s.pop();
                if (top->op == '(')
                {
                    break;
                }
                result.push_back(top);
            }
        }
    }

    // 后缀表达式不含括号，不用实现
    virtual void performInEvaluaion(std::stack<Number *> &s) override
    {
    }
    virtual void performInAstConstruction(std::stack<Node *> &s) override
    {
    }
    virtual void print() const override
    {
        std::cout << op << "\n";
    }
};

class Solution
{
public:
    int calculate(string s)
    {
        vector<Token *> tokens = lex(s);
        vector<Token *> postFix = convert2PostFix(tokens);
        return getResultFromPostFix(postFix);
    }

private:
    static bool isOperator(const char c)
    {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }
    static bool isBracket(const char c)
    {
        return c == '(' || c == ')';
    }

    // 词法分析（轻量级DFA）
    vector<Token *> lex(string s)
    {
        int n = s.length();
        vector<Token *> tokens;

        bool readingNumber = false;
        int readNumber = 0;
        for (const char c : s)
        {

            if (isdigit(c))
            {
                readingNumber = true;
                readNumber *= 10;
                readNumber += (c - '0');
            }
            else
            {
                if (readingNumber)
                {
                    tokens.push_back(new Number(readNumber));
                    readingNumber = false;
                    readNumber = 0;
                }
                if (isBracket(c))
                {
                    tokens.push_back(new Bracket(c));
                }
                else if (isOperator(c))
                {
                    // 不太优雅：为了避免将 - 当作一元运算符解释，在一元的 - 前面插入一个 0
                    if (c == '-')
                    {
                        if (tokens.empty() == true)
                        {
                            tokens.push_back(new Number(0));
                        }
                        else
                        {
                            // 回头看一步
                            Operator *top = dynamic_cast<Operator *>(tokens.back());
                            if (top != nullptr && top->op == '(')
                            {
                                tokens.push_back(new Number(0));
                            }
                        }
                    }
                    tokens.push_back(new Operator(c));
                }
            }
        }

        if (readingNumber)
        {
            tokens.push_back(new Number(readNumber));
        }

        return tokens;
    }

    // 中缀 token 转换为 后缀 token
    vector<Token *> convert2PostFix(const vector<Token *> &inFix)
    {
        std::stack<Operator *> s;
        vector<Token *> result;

        for (const auto token : inFix)
        {
            token->performInConvertion(result, s);
        }

        // 把剩下的表达式也放回去
        while (s.empty() == false)
        {
            result.push_back(s.top());
            s.pop();
        }

        return result;
    }

    // 后缀token直接求值
    int getResultFromPostFix(const vector<Token *> &postFix)
    {
        std::stack<Number *> s;

        for (const auto token : postFix)
        {
            token->performInEvaluaion(s);
        }

        return s.top()->value;
    }

    vector<Token *> getPostFixTokensFromStringVector(vector<string> &tokensString)
    {
        vector<Token *> tokens;
        for (const string s : tokensString)
        {
            if (s.length() == 1 && isOperator(s[0]))
            {
                tokens.push_back(new Operator(s[0]));
            }
            else
            {
                tokens.push_back(new Number(std::stoi(s)));
            }
        }
        return tokens;
    }

    void printTokens(const vector<Token *> &tokens)
    {
        for (const auto token : tokens)
        {
            token->print();
        }
    }

    Node *constructAstFromPostfix(const vector<Token *> &postfix)
    {
        std::stack<Node *> s;

        for (const auto token : postfix)
        {
            token->performInAstConstruction(s);
        }

        return s.top();
    }

public:
    Node *expTree(string s)
    {
        vector<Token *> infix = lex(s);
        vector<Token *> postfix = convert2PostFix(infix);
        return constructAstFromPostfix(postfix);
    }

    int evalRPN(vector<string> &tokens)
    {
        vector<Token *> postFix = getPostFixTokensFromStringVector(tokens);
        return getResultFromPostFix(postFix);
    }
};

int main()
{
    Solution s;
    s.expTree("3*(9-6*5)");
    return 0;
}