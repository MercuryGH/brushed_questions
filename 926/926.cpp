#include <string>
#include <vector>
#include <algorithm>
using std::string, std::vector;

class Solution
{
public:
    int minFlipsMonoIncr(string s)
    {
        const int n = s.length();
        vector<int> dp1(n), dp2(n);
        dp1[0] = s[0] == '1';
        dp2[0] = s[0] == '0';

        for (int i = 1; i < n; i++) {
            dp1[i] = dp1[i - 1] + (s[i] == '1');
            dp2[i] = std::min(dp1[i - 1], dp2[i - 1]) + (s[i] == '0');
        }
        return std::min(dp1[n - 1], dp2[n - 1]);
    }
};