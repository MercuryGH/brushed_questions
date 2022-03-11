#include <vector>
using std::vector;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/**
 * 从先序遍历序列构造二叉搜索树
 * 本体相当于从插入序列构造二叉搜索树。这是因为 BST 的先序遍历序列必然满足
 * 根（左）（右）即 中（小）（大）的 规律，且递归下去仍满足此规律。
 * 这意味着将先序序列看作插入序列，也能得到正确的结果
 */
class Solution {
    TreeNode *insert(TreeNode *root, int num) {
        if (root == nullptr) {
            return new TreeNode(num);
        }
        if (num <= root->val) {
            root->left = insert(root->left, num);
        } else {
            root->right = insert(root->right, num);
        }
        return root;
    }
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        TreeNode *root = nullptr;
        for (const int num : preorder) {
            root = insert(root, num);
        }
        return root;
    }
};

/**
 * 思维相对简单的版本
 * 其实更推荐
 */
class BetterSolution {
    void insert(TreeNode *const root, int num) {
        if (root == nullptr) {
            return;
        }

        if (num <= root->val) {
            if (root->left == nullptr) {
                root->left = new TreeNode(num);
            } else {
                insert(root->left, num);
            }
        } else {
            if (root->right == nullptr) {
                root->right = new TreeNode(num);
            } else {
                insert(root->right, num);
            }            
        }
    }
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        TreeNode *root = new TreeNode(preorder[0]);
        const int n = preorder.size();
        for (int i = 1; i < n; i++) {
            insert(root, preorder[i]);
        }
        return root;
    }
};