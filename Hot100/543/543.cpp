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
 * 二叉树的直径。DFS暴力题
 * key idea: 任意一条路径均可以被看作由某个节点为起点，从其左儿子和右儿子向下遍历的路径拼接得到。
 */
class Solution
{
    int ans;
    int depth(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }

        const int lDepth = (root->left) ? depth(root->left) : 0;
        const int rDepth = (root->right) ? depth(root->right) : 0;
        this->ans = std::max(this->ans, lDepth + rDepth + 1);
        return std::max(lDepth, rDepth) + 1;
    }
public:
    int diameterOfBinaryTree(TreeNode *root)
    {
        this->ans = 1;
        depth(root);
        return ans - 1;
    }
};