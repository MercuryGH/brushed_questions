class Solution
{
    long long trailingZeroes(long long n)
    {
        long long ans = 0;
        for (long long cur = 5;; cur *= 5)
        {
            if (n / cur == 0)
            {
                break;
            }
            ans += (n / cur);
        }
        return ans;
    }

public:
    int preimageSizeFZF(int k)
    {
        long long l = 4ll * k;
        long long r = 5ll * k;
        while (true) {
            if (l > r) {
                return 0;
            }

            const long long mid = (r - l) / 2 + l;
            const long long zeroNum = trailingZeroes(mid);
            if (zeroNum == k) {
                return 5;
            } else if (zeroNum < k) {
                l = mid + 1;
            } else { // zeroNum > k
                r = mid - 1;
            }
        }
        return 0;
    }
};