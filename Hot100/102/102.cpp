#include <vector>
#include <queue>
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
 * BFS，层序遍历典型题
 * 建议背诵
 */
class Solution
{
public:
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        if (root == nullptr) {
            return {};
        }

        vector<vector<int>> ans;
        std::queue<TreeNode *> q;
        q.push(root);

        while (q.empty() == false) {
            int levelSize = q.size();
            std::vector<int> levelRes;
            while (levelSize--) {
                TreeNode *nextNode = q.front();
                q.pop();
                levelRes.push_back(nextNode->val);
                if (nextNode->left != nullptr) {
                    q.push(nextNode->left);
                }
                if (nextNode->right != nullptr) {
                    q.push(nextNode->right);
                }
            }
            ans.push_back(levelRes);
        }
        return ans;
    }
};

