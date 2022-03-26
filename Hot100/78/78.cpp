#include <vector>
using std::vector;

/**
 * 返回nums的幂集
 * 深度DFS思想：每个元素要么被选中，要么不被选中。
 * 层级DFS思想：每次选元素，只能选后面的元素，而且可以选个空集然后结束
 */
class Solution {
    int n;
    
    void dfs(const vector<int> &nums, vector<vector<int>> &ansSet, vector<int> &curSet, int index) {
        if (index == n) {
            ansSet.push_back(curSet);
            return;
        }

        // 通用层级 DFS
        for (int i = index; i <= n; i++) {
            if (i == n) { // 选了个空集，特判
                dfs(nums, ansSet, curSet, i);
            } else {
                curSet.push_back(nums[i]);
                dfs(nums, ansSet, curSet, i + 1);
                curSet.pop_back();
            }
        }

        // 另一种思路（不通用的深度DFS），现在不推荐了
        // const int element = nums[curIndex];
        // curSet.push_back(element);
        // dfs(nums, ansSet, curSet, curIndex + 1);  // 选中
        // curSet.pop_back();
        // dfs(nums, ansSet, curSet, curIndex + 1);  // 不选中
    }

public:
    vector<vector<int>> subsets(vector<int>& nums) {
        n = nums.size();
        vector<vector<int>> ansSet;
        vector<int> curSet;
        dfs(nums, ansSet, curSet, 0);
        return ansSet;
    }
};
