#include <string>
#include <vector>
#include <iostream>
using std::vector;
using std::string;

class Solution {
public:
    long long coutPairs(vector<int>& nums, int k) {
        const int n = nums.size();
        vector<bool> prev = vector<bool>(n);
        vector<int> smallNums;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            prev[i] = (nums[i] % k == 0);
            if (prev[i] == true) {
                cnt++;
            }
            if (nums[i] < k) {
                smallNums.push_back(nums[i]);
            }
        }

        const int m = smallNums.size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                
            }
        }
        int pp = cnt * (n - cnt) + (cnt - 1) * cnt / 2;
    }
};

int main() {
    vector<int> nums = {8, 2, 16, 4, 5};
    int k = 2;
    Solution s;
    std::cout << s.coutPairs(nums, k) << "\n";
    return 0;
}