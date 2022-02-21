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
 * 合并两个二叉树，相同结点需要进行val相加
 * 注意，不是在原二叉树的基础上合并，而是要开辟额外空间，然后返回结果的根
 * DFS很方便
 */
class Solution
{
public:
    TreeNode *mergeTrees(TreeNode *t1, TreeNode *t2)
    {
        if (t1 == nullptr)
        {
            return t2;
        }
        if (t2 == nullptr)
        {
            return t1;
        }

        TreeNode *merged = new TreeNode(t1->val + t2->val);
        const bool t1HasLeftChild = t1->left != nullptr;
        const bool t1HasRightChild = t1->right != nullptr;
        const bool t2HasLeftChild = t2->left != nullptr;
        const bool t2HasRightChild = t2->right != nullptr;

        if (t1HasLeftChild && t2HasLeftChild)
        {
            merged->left = mergeTrees(t1->left, t2->left);
        }
        else if (t1HasLeftChild)
        {
            merged->left = t1->left;
        }
        else if (t2HasLeftChild)
        {
            merged->left = t2->left;
        }
        else
        {
            merged->left = nullptr;
        }

        if (t1HasRightChild && t2HasRightChild)
        {
            merged->right = mergeTrees(t1->right, t2->right);
        }
        else if (t1HasRightChild)
        {
            merged->right = t1->right;
        }
        else if (t2HasRightChild)
        {
            merged->right = t2->right;
        }
        else
        {
            merged->right = nullptr;
        }

        return merged;
    }
};
