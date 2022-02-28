#include <algorithm>
#include <utility>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
    /**
     * 返回值：(f_{root, 0}, f_{root, 1})
     */
    std::pair<int, int> dp(TreeNode *root)
    {
        if (root == nullptr)
        {
            return {0, 0};
        }

        const auto left = dp(root->left);
        const auto right = dp(root->right);
        return {
            std::max(left.first, left.second) + std::max(right.first, right.second),
            root->val + left.first + right.first
        };
    }

public:
    int rob(TreeNode *root)
    {
        const auto res = dp(root);
        return std::max(res.first, res.second);
    }
};