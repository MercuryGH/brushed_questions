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

struct Token
{
    virtual void modifyStack(std::stack<int> &s) const = 0;
    virtual void print() const = 0;
};
struct Number : Token
{
    int value;
    Number(int value) : value(value) {}

    virtual void modifyStack(std::stack<int> &s) const override
    {
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

    virtual void modifyStack(std::stack<int> &s) const override
    {
    }
    virtual void print() const override
    {
        std::cout << op << "\n";
    }
};
struct Bracket : Token
{
    char bracket;
    Bracket(char bracket) : bracket(bracket) {}

    virtual void modifyStack(std::stack<int> &s) const override
    {
    }
    virtual void print() const override
    {
        std::cout << bracket << "\n";
    }
};

class Solution
{
public:
    int calculate(string s)
    {
        vector<Token *> tokens = lex(s);
        for (const auto token : tokens) {
            token->print();
        }
        return 0;
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

    int calculate(vector<Token *> tokens, int start, int end)
    {
        std::stack<int> s;
        bool positive = false;
        int index = start;
        while (true)
        {
            if (index > end)
            {
                break;
            }

            Token *curToken = tokens[index];
            curToken->modifyStack(s);
            index++;
        }
    }
};

int main() {
    Solution s;
    s.calculate("1 + 2 - 3 * (4 + 5)");
    return 0;
}