#include <vector>
#include <unordered_set>

class Solution {
public:
    bool containsNearbyDuplicate(std::vector<int>& nums, int k) {
        int n = nums.size();
        std::unordered_set<int> slideWindow;
        for (int i = 0; i < n; i++) {
            int curNum = nums[i];
            if (i > k) {
                int firstOut = nums[i - k - 1];
                slideWindow.erase(firstOut);  // 往右滑一格
            }
            if (slideWindow.find(curNum) != slideWindow.end()) {
                return true;
            }
            slideWindow.insert(curNum);  // 装进去
        }
        return false;
    }
};