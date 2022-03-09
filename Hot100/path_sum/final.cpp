#include <algorithm>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/**
 * 二叉树中的最大路径和
 */
class Solution
{
    int dp(int &maxSum, TreeNode *node) {
        if (node == nullptr) {
            return 0;
        }
        const int lDp = dp(maxSum, node->left);
        const int rDp = dp(maxSum, node->right);
        const int curDp = std::max(lDp, std::max(rDp, 0)) + node->val;

        const int curSum = std::max(lDp, 0) + std::max(rDp, 0) + node->val;
        maxSum = std::max(maxSum, curSum);

        return curDp;
    }
public:
    int maxPathSum(TreeNode *root)
    {
        int maxSum = INT_MIN;
        dp(maxSum, root);
        return maxSum;
    }
};
