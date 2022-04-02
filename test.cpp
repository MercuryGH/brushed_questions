#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::vector, std::string;

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
     * 
     * 注意：本方法没有建立哈希表加速，因为preorder, inorder中可能存在重复值
     */
    TreeNode *dfs(const vector<int> &preorder, const vector<int> &inorder)
    {
        if (preorder.empty() || inorder.empty()) {
            return nullptr;
        }

        const int rootVal = preorder[0];
        const int inRootIndex = findIndex(inorder, rootVal);  // 中序遍历中，根的位置

        TreeNode *root = new TreeNode(rootVal);  // 用val构建根

        vector<int> leftPreorder;
        vector<int> rightPreorder;
        vector<int> leftInorder;
        vector<int> rightInorder;
        std::move(preorder.begin() + 1, preorder.begin() + inRootIndex + 1, leftPreorder.begin());
        std::move(preorder.begin() + inRootIndex + 1, preorder.end(), rightPreorder.begin());
        std::move(inorder.begin(), inorder.begin() + inRootIndex, leftInorder.begin());
        std::move(inorder.begin() + inRootIndex + 1, inorder.end(), rightInorder.begin());

        root->left = dfs(leftPreorder, leftInorder);
        root->right = dfs(rightPreorder, rightInorder);
        return root;
    }

    int findIndex(const vector<int> &inorder, const int val) {
        for (int i = 0; i < inorder.size(); i++) {
            if (inorder[i] == val) {
                return i;
            }
        }
        return -1;
    }

public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        const int n = preorder.size();
        return dfs(preorder, inorder);
    }
};


int main()
{

    vector<int> a = {1, 2, 3, 4, 5};
    vector<int> b = {3,3,3,3,3};
    std::move(a.begin(), a.end(), b.begin());

    for (const int num : b) {
        std::cout << num << "\n";
    }

    return 0;
}