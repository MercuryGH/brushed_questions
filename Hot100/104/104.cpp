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
 * DFS 求二叉树的高度
 * 实际上是树型DP
 */
class Solution
{
public:
    int maxDepth(TreeNode *root)
    {
        if (root == nullptr) {
            return 0;
        }

        const int leftMaxDepth = (root->left) ? maxDepth(root->left) : 0;
        const int rightMaxDepth = (root->right) ? maxDepth(root->right) : 0;
        return std::max(leftMaxDepth, rightMaxDepth) + 1;
    }
};