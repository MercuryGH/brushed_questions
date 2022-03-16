#include <algorithm>
#include <ctime>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <stack>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::vector, std::string;

class Solution
{
public:
    string largestNumber(vector<int> &nums)
    {
        vector<string> numStrs;
        for (const int num : nums) {
            numStrs.push_back(std::to_string(num));
        }

        const auto cmp = [](string a, string b)
        {
            return a + b > b + a;
        };
        std::sort(numStrs.begin(), numStrs.end(), cmp);

        string ans;
        for (const auto &numStr : numStrs)
        {
            ans += numStr;
        }

        int k = 0;
        while (k < ans.length() - 1 && ans[k] == '0') {
            k++; // 消除前导零
        }

        return ans.substr(k);
    }
};