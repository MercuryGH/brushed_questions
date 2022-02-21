#include <vector>

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
 * 二叉树的中序遍历
 * 注意inorder()的首次判断 root == nullptr 属于保险行为，实际上可以去掉
 */
class Solution
{
    void inorder(TreeNode *root, std::vector<int> &res)
    {
        if (root == nullptr)
        {
            return;
        }

        if (root->left != nullptr)
        {
            inorder(root->left, res);
        }
        res.push_back(root->val);
        if (root->right != nullptr)
        {
            inorder(root->right, res);
        }
    }

public:
    std::vector<int> inorderTraversal(TreeNode *root)
    {
        std::vector<int> res;
        if (root != nullptr)
        {
            inorder(root, res);
        }
        return res;
    }
};