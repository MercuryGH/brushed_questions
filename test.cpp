#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
#include <map>
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

/*
给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列。 
*/
class Solution
{
    int n;
    void dfs(std::vector<std::vector<int>> &permutations, std::vector<int> &cur, std::vector<bool> &vis, const std::vector<int> &nums, int step) {
        if (step == n) {
            permutations.push_back(cur);
            return;
        }

        for (int i = 0; i < n; i++) {
            if (i > 0 && nums[i] == nums[i - 1] && vis[i - 1] == false) {
                continue;
            }
            if (vis[i] == false) {
                vis[i] = true;
                cur.push_back(nums[i]);
                dfs(permutations, cur, vis, nums, step + 1);
                cur.pop_back();
                vis[i] = false;
            }
        }
    }
public:
    std::vector<std::vector<int>> permuteUnique(std::vector<int> &nums)
    {
        std::sort(nums.begin(), nums.end());
        n = nums.size();
        std::vector<std::vector<int>> ans;
        std::vector<bool> vis(n, false);
        std::vector<int> cur;
        dfs(ans, cur, vis, nums, 0);
        return ans;
    }
};

int main()
{
}