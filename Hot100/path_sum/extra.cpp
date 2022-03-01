#include <vector>
using std::vector;

class Solution
{
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    void dfs(TreeNode *node, int curSum, int &ans) {
        if (node == nullptr) {
            return;
        }
        if (node->left == nullptr && node->right == nullptr) {
            ans += node->val + curSum;
            return;
        }
        dfs(node->left, node->val + curSum, ans);
        dfs(node->right, node->val + curSum, ans);
    }

public:
    int pathSum(vector<int> &nums)
    {
        const int n = nums.size();
        TreeNode *root = new TreeNode(nums[0] % 10);
        for (int i = 1; i < n; i++) {
            const int curNum = nums[i];
            const int depth = curNum / 100;
            const int pos = curNum / 10 % 10 - 1;
            const int val = curNum % 10;

            TreeNode *cur = root;
            for (int d = depth - 2, p = pos; d >= 0; d--) {
                if (p < (1 << d)) { // 在当前结点的左孩子
                    if (cur->left == nullptr) {
                        cur->left = new TreeNode(val);
                    }
                    cur = cur->left;
                } else {
                    if (cur->right == nullptr) {
                        cur->right = new TreeNode(val);
                    }
                    cur = cur->right;
                }
                p %= (1 << d);
            }
        }
        int ans = 0;
        dfs(root, 0, ans);
        return ans;
    }
};

