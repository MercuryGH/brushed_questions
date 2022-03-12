#include <string>
#include <vector>
using std::string, std::vector;

class Solution
{
public:
    int numDecodings(string s)
    {
        const int n = s.length();
        if (s[0] == '0') { // 前缀为0，答案必为0
            return 0;
        }
        if (n == 1) {
            return s[0] != '0';
        }

        vector<int> dp(n);
        dp[n - 1] = s[n - 1] == '0' ? 0 : 1;
        if (s[n - 2] == '1' || s[n - 2] == '2' && s[n - 1] <= '6') {
            dp[n - 2] = dp[n - 1] + 1;
        } else if (s[n - 2] != '0') {
            dp[n - 2] = dp[n - 1];
        } else {
            dp[n - 2] = 0;
        }

        for (int i = n - 3; i >= 0; i--) {
            if (s[i] == '1' || s[i] == '2' && s[i + 1] <= '6') {
                dp[i] = dp[i + 1] + dp[i + 2];
            } else if (s[i] != '0') {
                dp[i] = dp[i + 1];
            } else {
                dp[i] = 0;
            }
        }

        return dp[0];
    }
};