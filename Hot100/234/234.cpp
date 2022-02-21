#include <vector>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/**
 * 回文链表
 * Naive解法是遍历一遍，存到字符串里面，然后判断字符串是否回文。时空复杂度均为 O(n)
 * 
 * 下列常数较大的 O(n) 解法可以让空间复杂度仅为 O(1)。步骤如下：
  * 1. 找到前半部分链表的尾节点。
    2. 反转后半部分链表。
    3. 判断是否回文。
    4. 恢复链表（该步骤可以省略，但会导致链表被修改）。
    5. 返回结果。
 */
class Solution
{
public:
    bool isPalindrome(ListNode *head)
    {
        std::vector<int> vals;
        for (ListNode *cur = head; cur; cur = cur->next) {
            vals.push_back(cur->val);
        }

        const int n = vals.size();
        for (int i = 0, j = n - 1; i < j; i++, j--) {
            if (vals[i] != vals[j]) {
                return false;
            }
        }
        return true;
    }
};
