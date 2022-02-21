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
 * 将二叉树镜像反转
 */
class Solution
{
public:
    TreeNode *invertTree(TreeNode *root)
    {
        if (root == nullptr) {
            return nullptr;
        }

        TreeNode *left = (root->left) ? invertTree(root->left) : nullptr;
        TreeNode *right = (root->right) ? invertTree(root->right) : nullptr;
        root->left = right;
        root->right = left;
        return root;
    }
};
