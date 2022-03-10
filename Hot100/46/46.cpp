#include <vector>

/**
 * 全排列
 * 建议全文背诵
 */
class Solution
{
    void dfs(std::vector<std::vector<int>> &permutations, std::vector<int> &cur, std::vector<bool> &vis, const std::vector<int> &nums, int step)
    {
        const int n = nums.size();
        if (step == n)
        {
            permutations.push_back(cur);
            return;
        }

        for (int i = 0; i < n; i++)
        {
            if (vis[i] == false)
            {
                vis[i] = true;
                cur.push_back(nums[i]);
                dfs(permutations, cur, vis, nums, step + 1);
                cur.pop_back();
                vis[i] = false;
            }
        }
    }

public:
    std::vector<std::vector<int>> permute(std::vector<int> &nums)
    {
        const int n = nums.size();
        std::vector<std::vector<int>> ans;
        std::vector<bool> vis(n, false);
        std::vector<int> cur;
        dfs(ans, cur, vis, nums, 0);
        return ans;
    }
};