#include <vector>
using std::vector;

class Solution {
public:
    int countPrimes(int n) {
        vector<bool> isPrime(n, true);

        int ans = 0;
        for (int i = 2; i < n; i++) {
            if (isPrime[i] == true) {
                ans++;
                for (int j = 2; i * j < n; j++) {
                    isPrime[i * j] = false;
                }
            }
        }
        return ans;
    }
};