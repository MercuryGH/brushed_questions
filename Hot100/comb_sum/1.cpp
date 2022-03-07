#include <vector>

/**
 * 组合总和
 * 策略：选或不选。不必记录vis数组。
 * candidates 中的 同一个 数字可以 无限制重复被选取 。如果至少一个数字的被选数量不同，则两种组合是不同的。 
 * 
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