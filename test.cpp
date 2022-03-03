#include <algorithm>
#include <vector>
#include <iostream>
#include <unordered_map>
using std::vector;

class Solution {
public:
    int integerBreak(int n) {
        vector<int> dp(n + 1, 0);
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= i - 1; j++) {
                dp[i] = std::max(dp[i], dp[i - j] * j);
                if (i != n) {
                    dp[i] = std::max(dp[i], i);
                }
            }
        }

        for (const auto num : dp) {
            std::cout << num << " ";
        }
        std::cout << "\n";


        return dp[n];
    }
};


int main()
{
    std::unordered_map<char, int> hash;
    hash['a'] = 1;
    hash['b']++;

    std::cout << (hash.find('c') == hash.end()) << "\n";
    std::cout << hash['a'] << " " << hash['b'] << " " << hash['c'] << "\n";
    std::cout << (hash.find('c') == hash.end()) << "\n";

    return 0;
}

