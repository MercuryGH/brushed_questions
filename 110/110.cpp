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

// 判断一棵树是否为平衡二叉树
class Solution
{
    bool alreadyInbalanced = false;

public:
    int getHeight(TreeNode *root)
    {
        if (alreadyInbalanced == true)
        {
            return -1;
        }
        if (root == nullptr)
        {
            return 0;
        }
        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);

        if (std::abs(leftHeight - rightHeight) > 1) // 发现不平衡
        {
            alreadyInbalanced = true;
        }

        return std::max(leftHeight, rightHeight) + 1;
    }

    bool isBalanced(TreeNode *root)
    {
        int height = getHeight(root);
        return alreadyInbalanced == false;
    }
};