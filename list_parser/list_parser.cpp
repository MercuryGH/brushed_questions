#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::vector, std::string;

class NestedInteger
{
public:
    // Constructor initializes an empty nested list.
    NestedInteger();

    // Constructor initializes a single integer.
    NestedInteger(int value);

    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Set this NestedInteger to hold a single integer.
    void setInteger(int value);

    // Set this NestedInteger to hold a nested list and adds a nested integer to it.
    void add(const NestedInteger &ni);

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const;
};

class Solution
{
    NestedInteger deserializeFrom(const string s, int &globalIndex)
    {
        if (s[globalIndex] != '[')
        {
            bool isNegative = false;
            if (s[globalIndex] == '-')
            {
                isNegative = true;
                globalIndex++;
            }
            int readNumber = 0;
            while (globalIndex < s.length() && isdigit(s[globalIndex]))
            {
                readNumber *= 10;
                readNumber += s[globalIndex] - '0';
                globalIndex++;
            }
            if (isNegative)
            {
                readNumber = -readNumber;
            }

            return NestedInteger(readNumber);
        }

        globalIndex++;
        NestedInteger ni;
        while (s[globalIndex] != ']')
        {
            ni.add(deserializeFrom(s, globalIndex));

            if (s[globalIndex] == ',')
            {
                globalIndex++;
            }
        }
        globalIndex++;
        return ni;
    }

public:
    NestedInteger deserialize(string s)
    {
        int globalIndex = 0;
        return deserializeFrom(s, globalIndex);
    }
};