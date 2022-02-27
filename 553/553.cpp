#include <vector>
#include <string>
using std::vector, std::string;

class Solution {
public:
    string optimalDivision(vector<int>& nums) {
        const int n = nums.size();
        if (n == 1) {
            return std::to_string(nums[0]);
        }
        if (n == 2) {
            return std::to_string(nums[0]) + "/" + std::to_string(nums[1]);
        }

        std::string ans = std::to_string(nums[0]) + "/(" + std::to_string(nums[1]);
        for (int i = 2; i < n; i++) {
            ans.append("/" + std::to_string(nums[i]));
        }
        ans.append(")");
        return ans;
    }
};