#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
#include <memory>
#include <numeric>
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

class Solution
{
public:
    // 先序遍历
    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> res;
        std::stack<TreeNode *> stk;
        TreeNode *node = root;
        while (true)
        {
            if (node == nullptr && stk.empty() == true) { // 都没了
                break;
            }
            while (true) // 找左
            {
                if (node == nullptr) {
                    break;
                }
                res.push_back(node->val);
                stk.push(node);
                node = node->left;
            }
            node = stk.top(); // 回退找右
            stk.pop();
            node = node->right;
        }
        return res;
    }

    // 中序遍历
    vector<int> inorderTraversal(TreeNode *root)
    {
        std::weak_ptr<int> s;
        s.lock();

        vector<int> res;
        std::stack<TreeNode *> stk;
        TreeNode *node = root;
        while (true)
        {
            if (node == nullptr && stk.empty() == true) { // 都没了
                break;
            }
            while (true)
            {
                if (node == nullptr) {
                    break;
                }
                stk.push(node);
                node = node->left;
            }
            node = stk.top();
            stk.pop();
            res.push_back(node->val);
            node = node->right;
        }
        return res;
    }

    // 后序遍历，使用 reverse 的先序遍历 （根右左）
    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> res;
        std::stack<TreeNode *> stk;
        TreeNode *node = root;
        while (true)
        {
            if (node == nullptr && stk.empty() == true) { // 都没了
                break;
            }

            while (true)
            {
                if (node == nullptr) {
                    break;
                }
                stk.push(node);
                res.push_back(node->val);
                node = node->right;
            }
            node = stk.top();
            stk.pop();
            node = node->left;
        }
        std::reverse(res.begin(), res.end());
        return res;
    }
};
