#include <vector>
using std::vector;

/**
 * 返回nums的幂集
 * 思想：每个元素要么被选中，要么不被选中。
 */
class Solution {
    int n;
    void dfs(const vector<int> &nums, vector<vector<int>> &ansSet, vector<int> &curSet, int curIndex) {
        if (curIndex == n) {
            ansSet.push_back(curSet);
            return;
        }

        const int element = nums[curIndex];

        curSet.push_back(element);
        dfs(nums, ansSet, curSet, curIndex + 1);  // 选中
        curSet.pop_back();

        dfs(nums, ansSet, curSet, curIndex + 1);  // 不选中
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        this->n = nums.size();
        vector<vector<int>> ansSet;
        vector<int> curSet;
        dfs(nums, ansSet, curSet, 0);
        return ansSet;
    }
};
