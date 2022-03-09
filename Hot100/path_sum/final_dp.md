# 二叉树中的最大路径和

## 树形DP

**定义** 以node为最高点的上升路径，指的是以node为根的子树，与其左子树或右子树选择其一所构成的任一路径。

记$f_{\text{node}}$为以node为最高点，所能达到的最大上升路径和。那么

$$
f_{\text{node}} = \max(f_{\text{node.left}}, f_{\text{node.right}}, 0) + \text{node.val}.
$$

终结条件为$f_{\text{null}} = 0$。

那么，我们要求的最大路径和，就是对任一树中的结点node，

$$
\max(f_{\text{node.left}},0) + \max(f_{\text{node.right}},0) + \text{node.val}
$$

的最大值。

最后必须加上 `node.val`，是因为题目规定不允许空路径。

```cpp
class Solution
{
    int dp(int &maxSum, TreeNode *node) {
        if (node == nullptr) {
            return 0;
        }
        const int lDp = dp(maxSum, node->left);
        const int rDp = dp(maxSum, node->right);
        const int curDp = std::max(lDp, std::max(rDp, 0)) + node->val;

        const int curSum = std::max(lDp, 0) + std::max(rDp, 0) + node->val;
        maxSum = std::max(maxSum, curSum);

        return curDp;
    }
public:
    int maxPathSum(TreeNode *root)
    {
        int maxSum = INT_MIN;
        dp(maxSum, root);
        return maxSum;
    }
};
```
