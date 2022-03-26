#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::vector, std::string;

class Solution
{
    int n;

    void dfs(vector<vector<int>> &ansSets, vector<int> &curSet, int index, const vector<int> &nums, const int size)
    {
        if (curSet.size() == size)
        {
            ansSets.push_back(curSet);
            return;
        }

        for (int i = index; i < n; i++)
        {
            if (i != index && nums[i] == nums[i - 1]) // 去重（要求 nums 有序）
                continue;

            curSet.push_back(nums[i]);
            dfs(ansSets, curSet, i + 1, nums, size);
            curSet.pop_back();
        }
    }

public:
    vector<vector<int>> subsetsWithDup(vector<int> &nums)
    {
        n = nums.size();
        vector<vector<int>> ans;
        vector<int> curSet;
        ans.push_back(curSet); // 加入空集
        std::sort(nums.begin(), nums.end()); // 去重

        for (int i = 1; i <= n; i++) // 找所有大小为 i 的子集
        {
            dfs(ans, curSet, 0, nums, i);
        }
        return ans;
    }
};