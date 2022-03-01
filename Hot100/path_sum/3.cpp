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
 * 思想：考虑每个结点都可能成为至少一个合法的路径的 **最下方** 的结点。
 * 我们将从根结点到该结点的路径之和记为 curSum，
 * 如果我们能够维护一个哈希表，其 
 *   - key 为从根结点到该结点，所以可能得到的前缀和；
 *   - value 为得到 key 为前缀和可能的方案数（例如 {1, -1, 1, -1} 有 2 种方案得到 0）
 * 那么，我们查表，找到key为 curSum - targetSum 的那个 value，减去之，就可以凑出一个合法的路径，其
 * 路径之和恰为 curSum - (curSum - targetSum) = targetSum. 
 */
class Solution
{
    int ans = 0;

    void dfs(TreeNode *root, const int curSum, const int targetSum, std::unordered_map<int, int> &hash) {
        if (hash.find(curSum - targetSum) != hash.end()) { // 减去某个前缀和可以解决问题
            ans += hash[curSum - targetSum];
        }
        hash[curSum]++;
        if (root->left) {
            dfs(root->left, curSum + root->left->val, targetSum, hash);
        }
        if (root->right) {
            dfs(root->right, curSum + root->right->val, targetSum, hash);
        }
        hash[curSum]--; // 回溯时要消去
    }
public:
    int pathSum(TreeNode *root, int targetSum)
    {
        if (root == nullptr) {
            return 0;
        }
        std::unordered_map<int, int> hash; // key: 能够凑出的前缀和, value: 凑出这个前缀和的方案数
        hash[0] = 1;
        dfs(root, root->val, targetSum, hash);

        return ans;
    }
};
