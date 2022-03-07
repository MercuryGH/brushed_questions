#include <algorithm>
#include <ctime>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::vector;

class Solution
{
    vector<vector<int>> twoSumTarget(const vector<int> &nums, const int startIndex, const int target)
    {
        const int n = nums.size();
        int l = startIndex;
        int r = n - 1;
        vector<vector<int>> ans;
        while (true)
        {
            if (l >= r)
            {
                break;
            }

            const int curL = nums[l];
            const int curR = nums[r];
            const int sum = curL + curR;
            if (sum == target)
            {
                ans.push_back({nums[l], nums[r]});
                while (l < r & nums[l] == curL)
                {
                    l++;
                }
                while (l < r && nums[r] == curL)
                {
                    r--;
                }
            }
            else if (sum < target)
            {
                while (l < r && nums[l] == curL)
                {
                    l++;
                }
            }
            else
            {
                while (l < r && nums[r] == curR)
                {
                    r--;
                }
            }
        }
        return ans;
    }

public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        const int n = nums.size();

        std::unordered_map<int, vector<int>> valToIndex;
        for (int i = 0; i < n; i++)
        {
            valToIndex[nums[i]].push_back(i);
        }

        std::sort(nums.begin(), nums.end());
        vector<int> ansVal = twoSumTarget(nums, 0, target)[0];
        vector<int> ansIndex = {
            valToIndex[ansVal[0]][0],
            valToIndex[ansVal[1]][0],
        };
        if (ansVal[0] == ansVal[1])
        {
            ansIndex = {
                valToIndex[ansVal[0]][0],
                valToIndex[ansVal[1]][1],
            };
        }

        return ansIndex;
    }
};

int main()
{
    Solution s;
    vector<int> nums = {6, 4, 3, 2, 7, 6, 2};

    return 0;
}