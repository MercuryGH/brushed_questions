struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution
{
    /**
     * 比较两树在根结点上，rootA是否是rootB的子结构
     */
    bool contains(TreeNode *rootA, TreeNode *rootB) {
        if (rootB == nullptr) {
            return true;
        }
        if (rootA == nullptr) {
            return false;
        }
        if (rootA->val != rootB->val) {
            return false;
        }

        const bool leftSame = contains(rootA->left, rootB->left);
        const bool rightSame = contains(rootA->right, rootB->right);
        return leftSame && rightSame;
    }

    bool found = false;

    /**
     * 遍历所有结点，调用 same()
     */
public:
    bool isSubStructure(TreeNode *A, TreeNode *B)
    {
        if (A == nullptr || B == nullptr) {
            return false;
        }
        if (found) {
            return true;
        }
        if (contains(A, B)) {
            found = true;
            return true;
        }
        
        (void)isSubStructure(A->left, B);
        if (found) {
            return true;
        }
        (void)isSubStructure(A->right, B);
        if (found) {
            return true;
        }
        return false;
    }
};