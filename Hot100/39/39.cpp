#include <vector>

/**
 * 典型DFS，建议背题
 */
class Solution
{
    void dfs(std::vector<std::vector<int>> &combinations, std::vector<int> &curCombination, const std::vector<int> &candidates, int target, int index) {
        if (target < 0) {  // 用于保险的剪枝，可以删
            return;
        }
        if (index == candidates.size()) {
            return;
        }
        if (target == 0) {
            combinations.push_back(curCombination);
            return;
        }

        dfs(combinations, curCombination, candidates, target, index + 1);  // 不选candidates[index]，下一步
        const int curSelectedNum = candidates[index];
        if (target - curSelectedNum >= 0) {
            curCombination.push_back(curSelectedNum);
            dfs(combinations, curCombination, candidates, target - curSelectedNum, index);  // 选candidates[index]，下一步
            curCombination.pop_back();
        }
    }
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int> &candidates, int target)
    {
        std::vector<std::vector<int>> ans;
        std::vector<int> combination;
        dfs(ans, combination, candidates, target, 0);
        return ans;
    }
};