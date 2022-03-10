#include <vector>
using std::vector;

class Node
{
public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val)
    {
        val = _val;
    }

    Node(int _val, vector<Node *> _children)
    {
        val = _val;
        children = _children;
    }
};

class Solution
{
    void dfs(vector<int> &ans, Node *node) {
        if (node == nullptr) {
            return;
        }
        ans.push_back(node->val);
        for (const auto child : node->children) {
            dfs(ans, child);
        }
    }
public:
    vector<int> preorder(Node *root)
    {
        vector<int> ans;
        dfs(ans, root);
        return ans;
    }
};