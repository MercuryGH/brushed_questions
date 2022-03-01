#include <vector>
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

class Solution
{
    void dfs(vector<vector<int>> &answer, vector<int> &curPath, TreeNode *curNode, const int curSum, const int targetSum) {
        if (curNode == nullptr) {
            return;
        }
        if (curNode->left == nullptr && curNode->right == nullptr) {
            if (curSum + curNode->val == targetSum) {
                curPath.push_back(curNode->val);
                answer.push_back(curPath);
                curPath.pop_back();
            }
            return;
        }

        curPath.push_back(curNode->val);
        dfs(answer, curPath, curNode->left, curSum + curNode->val, targetSum);
        dfs(answer, curPath, curNode->right, curSum + curNode->val, targetSum);
        curPath.pop_back();
    }
public:
    vector<vector<int>> pathSum(TreeNode *root, int targetSum)
    {
        vector<vector<int>> answer;
        vector<int> curPath;
        dfs(answer, curPath, root, 0, targetSum);
        return answer;
    }
};