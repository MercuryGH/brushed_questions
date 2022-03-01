#include <unordered_map>

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
 * 路径总和 III
 * 
 * 1. 暴力解【嵌套DFS】：对每个结点，要么最终至少一个合法的路径包含该结点，且该结点位于最上方，要么并非如此。
 *   - 对于包含的情况，以其为根开搜。
 *   - 对于不包含的情况，递归其左右子结点。
 */
class BadSolution
{
    int ans = 0;

    void dfs(TreeNode *root, const int targetSum) {
        if (root == nullptr) {
            return;
        }

        dfsGetPath(root, root->val, targetSum);
        dfs(root->left, targetSum);
        dfs(root->right, targetSum);
    }
    void dfsGetPath(TreeNode *root, const int curSum, const int targetSum) {
        if (root == nullptr) {
            return;
        }
        if (curSum == targetSum) {
            ans++;
            // return; 这里不能停，后面可能还有
        }

        if (root->left) {
            dfsGetPath(root->left, curSum + root->left->val, targetSum);
        }
        if (root->right) {
            dfsGetPath(root->right, curSum + root->right->val, targetSum);
        }
    }

public:
    int pathSum(TreeNode *root, int targetSum)
    {
        dfs(root, targetSum);
        return ans;
    }
};

/**
 * 2. 前缀和优化
 */
class Solution
{
    int ans = 0;

    void dfs(TreeNode *root, const int curSum, const int targetSum, std::unordered_map<int, int> &hash) {
        if (hash.find(curSum - targetSum) != hash.end()) { // 哈希表中有
            ans += hash[curSum - targetSum];
        }
        hash[curSum]++;
        if (root->left) {
            dfs(root->left, curSum + root->left->val, targetSum, hash);
        }
        if (root->right) {
            dfs(root->right, curSum + root->right->val, targetSum, hash);
        }
        hash[curSum]--;
    }
public:
    int pathSum(TreeNode *root, int targetSum)
    {
        if (root == nullptr) {
            return 0;
        }
        std::unordered_map<int, int> hash;
        hash[0] = 1;
        dfs(root, root->val, targetSum, hash);

        return ans;
    }
};
/**
 * class Solution {
    void dfs(TreeNode root, int val) {
        if (map.containsKey(val - t)) ans += map.get(val - t);
        map.put(val, map.getOrDefault(val, 0) + 1);
        if (root.left != null) dfs(root.left, val + root.left.val);
        if (root.right != null) dfs(root.right, val + root.right.val);
        map.put(val, map.getOrDefault(val, 0) - 1);
    }
}
 */