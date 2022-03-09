struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * LCA 模板题
 * 
 * 三种情况可以直接确定LCA：
 * 1. p 和 q 在 root 的异侧：root 就是 LCA
 * 2. p == root, q 是 root 的后代：p 就是 LCA
 * 3. q == root, p 是 root 的后代：q 就是 LCA
 * 其他情况：
 * 4. p 和 q 在 root 的同侧：递归搜索 root 的那一侧即可。
 * 5. p 和 q 都不是 root 的后代：回溯！！
 */
class BadSolution // 时间复杂度为 O(n log n) 的暴力算法
{
    static bool dfs(TreeNode *root, TreeNode *target) {
        if (root == nullptr) {
            return false;
        }
        if (root == target) {
            return true;
        }
        return dfs(root->left, target) || dfs(root->right, target);
    }
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (root == nullptr) {
            return nullptr;
        }
        // 如果p,q为根节点，则公共祖先为根节点，找到
        if (root == p || root == q) {
            return root;
        }
        // 如果p,q在左子树，则公共祖先在左子树查找
        if (dfs(root->left, p) && dfs(root->left, q)) {
            return lowestCommonAncestor(root->left, p, q);
        }
        // 如果p,q在右子树，则公共祖先在右子树查找
        if (dfs(root->right, p) && dfs(root->right, q)) {
            return lowestCommonAncestor(root->right, p, q);
        }

        // 如果p,q分属两侧，则公共祖先为根节点，找到
        return root;
    }
};

class Solution // 时间复杂度为 O(n) 的优化
{
    TreeNode *ans;

    bool dfs(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (root == nullptr) {
            return false;
        }
        bool lSon = dfs(root->left, p, q);
        bool rSon = dfs(root->right, p, q);

        /** 
         * p 和 q 在 root 的异侧
         * 或者 p = root, q 是 root 的后代
         * 或者 q = root, p 是 root 的后代
         * 直接确定 LCA 的后代
         */ 
        if ((lSon && rSon) || root == p || root == q) {
            ans = root;  // 注意 ans 会在回溯过程中更新，并不是第一次更新就确定了
            return true;
        }
        return lSon || rSon; // 如果还有后代，就还有希望；否则回溯
    }
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        dfs(root, p, q);  // assert return value == true
        return ans;
    }
};

/**
 * 简洁明了，非常适合背诵的代码。时间复杂度也是最优的 O(n)
 */
class BeautifulSolution 
{
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (root == nullptr || root == p || root == q) {
            return root;
        }
        TreeNode *leftAns = lowestCommonAncestor(root->left, p, q);
        TreeNode *rightAns = lowestCommonAncestor(root->right, p, q);
        // 如果left为空，说明这两个节点在cur (root)结点的右子树上，我们只需要返回右子树查找的结果即可
        if (leftAns == nullptr) {
            return rightAns;
        }
        // 同上
        if (rightAns == nullptr) {
            return leftAns;
        }
        // 如果left和right都不为空，说明这两个节点一个在cur的左子树上一个在cur的右子树上，
        // 我们只需要返回cur结点即可。
        return root;
    }    
};