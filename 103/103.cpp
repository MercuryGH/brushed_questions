#include <vector>
#include <stack>
#include <queue>
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

class Solution
{
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {
        if (root == nullptr)
        {
            return {};
        }

        std::queue<TreeNode *> q;
        std::stack<TreeNode *> s;
        vector<vector<int>> ans;
        q.push(root);
        bool direction = 0;

        while (q.empty() == false)
        {
            int curLevelSize = q.size();
            direction = !direction;

            vector<int> level;
            while (curLevelSize--)
            {
                TreeNode *nextNode = q.front();
                q.pop();
                level.push_back(nextNode->val);

                if (direction == 0)
                {
                    if (nextNode->right)
                    {
                        s.push(nextNode->right);
                    }
                    if (nextNode->left)
                    {
                        s.push(nextNode->left);
                    }
                }
                else
                {
                    if (nextNode->left)
                    {
                        s.push(nextNode->left);
                    }
                    if (nextNode->right)
                    {
                        s.push(nextNode->right);
                    }
                }
            }
            ans.push_back(level);

            while (s.empty() == false) {
                TreeNode *popedNode = s.top();
                s.pop();
                q.push(popedNode);
            }
        }
        return ans;
    }
};