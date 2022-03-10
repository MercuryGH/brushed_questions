#include <queue>
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
public:
    vector<int> rightSideView(TreeNode *root)
    {
        vector<int> ans;
        std::queue<TreeNode *> q;
        if (root != nullptr)
            q.push(root);

        while (q.empty() == false)
        {
            int levelSize = q.size();
            TreeNode *nextNode;
            while (levelSize--)
            {
                nextNode = q.front();
                q.pop();
                if (nextNode->left)
                {
                    q.push(nextNode->left);
                }
                if (nextNode->right)
                {
                    q.push(nextNode->right);
                }
            }
            ans.push_back(nextNode->val);
        }
        return ans;
    }
};