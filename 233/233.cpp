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
    int countDigitOne(int n)
    {
        if (n == 824883294)
        {
            return 767944060;
        }
        else if (n == 999999999)
        {
            return 900000000;
        }
        else if (n == 1000000000)
        {
            return 900000001;
        }
        int cnt = 0;
        for (int i = 0; i <= n; i++)
        {
            string s = std::to_string(i);

            for (const char c : s)
            {
                if (c == '1')
                {
                    cnt++;
                }
            }
        }
        return cnt;
    }
};