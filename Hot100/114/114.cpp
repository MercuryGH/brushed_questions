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
 * 二叉树先序遍历展开成链表
 * 只会暴力
 */
class Solution
{
    std::vector<TreeNode *> traverseRes;
    void dfs(TreeNode *root) {
        if (root == nullptr) {
            return;
        }

        traverseRes.push_back(root);
        if (root->left) {
            dfs(root->left);
        }
        if (root->right) {
            dfs(root->right);
        }
    }
public:
    void flatten(TreeNode *root)
    {
        if (root == nullptr) {
            return;
        }

        dfs(root);
        const int n = traverseRes.size();
        for (int i = 0; i < n - 1; i++) {
            TreeNode *treeNode = traverseRes[i];
            treeNode->left = nullptr;
            treeNode->right = traverseRes[i + 1];
        }
        traverseRes[n - 1]->left = nullptr;
        traverseRes[n - 1]->right = nullptr;
    }
};