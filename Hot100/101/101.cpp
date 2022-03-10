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
 * 轴对称二叉树
 */
class Solution
{
    bool check(TreeNode *p, TreeNode *q)
    {
        // 保险语句，可以去掉
        if (p == nullptr && q == nullptr)
        {
            return true;
        }
        if (p == nullptr || q == nullptr)
        {
            return false;
        }
        // 保险语句结束

        const bool pHasLeftChild = p->left != nullptr;
        const bool pHasRightChild = p->right != nullptr;
        const bool qHasLeftChild = q->left != nullptr;
        const bool qHasRightChild = q->right != nullptr;
        //    ((pHasLeftChild && !qHasRightChild) ||
        //     (pHasRightChild && !qHasLeftChild) ||
        //     (!pHasLeftChild && qHasRightChild) ||
        //     (!pHasRightChild && qHasLeftChild))
        const bool pqHasOuterChild = pHasLeftChild ^ qHasRightChild == false; // 异或改写更简洁
        const bool pqHasInnerChild = pHasRightChild ^ qHasLeftChild == false;
        // 以下为卫语句
        if (p->val != q->val)
        {
            return false;
        }

        if (pqHasInnerChild == false || pqHasOuterChild == false)
        {
            return false;
        }

        bool hasSameOutterChild = true; // 远离对称轴的孩子对称
        bool hasSameInnerChild = true;  // 接近对称轴的孩子对称
        if (pHasLeftChild && qHasRightChild)
        {
            hasSameInnerChild = check(p->left, q->right);
        }
        if (pHasRightChild && qHasLeftChild)
        {
            hasSameOutterChild = check(p->right, q->left);
        }
        return hasSameOutterChild && hasSameInnerChild;
    }

public:
    bool isSymmetric(TreeNode *root)
    {
        if (root == nullptr) {
            return true;
        }
        return check(root, root);
    }
};
