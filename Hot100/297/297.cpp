#include <sstream>
#include <string>
#include <vector>
using std::vector, std::string;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * 二叉树的串行化和反串行化
 * 最简单的写法（先序加null码 #）
 */
class Codec
{
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode *root)
    {
        if (root == nullptr)
        {
            return "#";
        }
        string valStr = std::to_string(root->val);
        string leftChild = serialize(root->left);
        string rightChild = serialize(root->right);
        return valStr + " " + leftChild + " " + rightChild; // 用空格自然分开
    }

    TreeNode *deseralizeIss(std::istringstream &ss)
    {
        string valStr;
        ss >> valStr;
        if (valStr == "#")
        {
            return nullptr;
        }

        TreeNode *node = new TreeNode(std::stoi(valStr));
        node->left = deseralizeIss(ss);
        node->right = deseralizeIss(ss);
        return node;
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data)
    {
        std::istringstream ss(data);
        return deseralizeIss(ss);
    }
};

