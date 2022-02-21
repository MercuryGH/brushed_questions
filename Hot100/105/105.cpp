#include <vector>
#include <unordered_map>
using std::vector;

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
 * 从前序与中序遍历序列构造二叉树
 * 超经典题，建议背诵。
 * 做题时一定要画图
 */
class Solution
{
    std::unordered_map<int, int> inOrderIndexMap;  // 从中序遍历数组的元素val到其下标的哈希

    /**
     * @brief 递归构建二叉树
     * 
     * @param preorder 先序遍历的完整数组
     * @param inorder 中序遍历的完整数组
     * @param preL 当前栈帧关心的先序遍历的子数组的开始下标（闭区间）
     * @param preR 当前栈帧关心的先序遍历的子数组的结束下标（闭区间）
     * @param inL 同上
     * @param inR 同上
     * @return TreeNode* 根结点
     */
    TreeNode *dfs(const vector<int> &preorder, const vector<int> &inorder, int preL, int preR, int inL, int inR)
    {
        if (preL > preR) {
            return nullptr;
        }

        const int preRoot = preL;  // 先序遍历中，根的位置
        const int inRoot = inOrderIndexMap[preorder[preRoot]];  // 中序遍历中，根的位置

        TreeNode *root = new TreeNode(preorder[preRoot]);  // 用val构建根
        const int leftSubTreeSize = inRoot - inL;
        root->left = dfs(preorder, inorder,
            preL + 1, 
            preL + leftSubTreeSize, 
            inL, 
            inRoot - 1
        );
        root->right = dfs(preorder, inorder,
            preL + leftSubTreeSize + 1,
            preR,
            inRoot + 1,
            inR
        );
        return root;
    }

public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        const int n = preorder.size();
        for (int i = 0; i < n; i++) {
            this->inOrderIndexMap[inorder[i]] = i;
        }
        return dfs(preorder, inorder, 0, n - 1, 0, n - 1);
    }
};
