struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/**
 * 判断链表是否有环
 * 可以用哈希装链表节点（开销大）来判断是否访问到了之前访问到的元素
 * 但其实快慢指针法最好
 */
class Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr) {
            return false;
        }

        ListNode *slow = head;
        ListNode *fast = head->next;
        while (true) {
            if (fast == slow) {
                return true;
            }
            if (fast == nullptr || fast->next == nullptr) {
                return false;
            }
            fast = fast->next->next;
            slow = slow->next;
        }
    }
};