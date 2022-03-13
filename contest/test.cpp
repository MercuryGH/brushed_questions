#include <algorithm>
#include <ctime>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <memory>
using std::vector, std::string;

class Solution
{
    int n;
    bool outOfBound(int x) {
        return x < 0 || x >= n;
    }
public:
    vector<int> findKDistantIndices(vector<int> &nums, int key, int k)
    {
        n = nums.size();
        vector<int> keyIndices;
        for (int i = 0; i < n; i++) {
            if (nums[i] == key) {
                keyIndices.push_back(i);
            }
        }

        vector<int> ans;
        for (const int keyIndex : keyIndices) {
            for (int i = keyIndex - k; i <= keyIndex + k; i++) {
                if (outOfBound(i) == false) {
                    ans.push_back(i);
                }
            }
        }
        return ans;
    }
};

int main()
{
    Solution s;
    vector<int> nums = {3,4,9,1,3,9,5};
    auto n = s.findKDistantIndices(nums, 9, 1);
    for (const int num : n) {
        std::cout << num << " ";
    }
    return 0;
}