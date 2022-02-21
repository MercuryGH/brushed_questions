#include <string>
#include <vector>
#include <unordered_map>
using std::vector;

class Solution
{
    long long gcd(long long a, long long b)
    {
        return a % b == 0 ? b : gcd(b, a % b);
    }

public:
    long long coutPairs(vector<int> &nums, int k)
    {
        const int n = nums.size();
        std::unordered_map<int, int> hash;

        for (const int num : nums)
            hash[gcd(num, k)]++;

        long long ans = 0;
        for (const auto [k1, v1] : hash)
        {
            for (const auto [k2, v2] : hash)
            {
                if (1LL * k1 * k2 % k == 0)
                {
                    if (k1 < k2)
                        ans += 1LL * v1 * v2;
                    else if (k1 == k2)
                        ans += 1LL * v1 * (v1 - 1) / 2;
                }
            }
        }
        return ans;
    }
};