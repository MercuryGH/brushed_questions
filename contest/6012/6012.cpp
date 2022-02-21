#include <iostream>

class Solution {
    int getSum(int n) {
        int ans = 0;
        while (true) {
            int lsb = n % 10;
            ans += lsb;
            n /= 10;
            if (n == 0) {
                return ans;
            }
        }
    }
public:
    int countEven(int num) {
        int cnt = 0;
        for (int i = 2; i <= num; i++) {
            if (getSum(i) % 2 == 0) {
                cnt++;
            }
        }
        return cnt;
    }
};

int main() {
    Solution s;
    std::cout << s.countEven(30) << "\n";
    return 0;
}