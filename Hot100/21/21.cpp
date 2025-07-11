struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        ListNode *dummy = new ListNode(-1);
        ListNode *cur = dummy;
        while (true)
        {
            if (l1 == nullptr || l2 == nullptr)
            {
                break;
            }
            if (l1->val < l2->val)
            {
                cur->next = l1;
                l1 = l1->next;
            }
            else
            {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }

        // 合并后 l1 和 l2 最多只有一个还未被合并完，我们直接将链表末尾指向未合并完的链表即可
        if (l1 == nullptr)
        {
            cur->next = l2;
        }
        if (l2 == nullptr)
        {
            cur->next = l1;
        }

        ListNode *ans = dummy->next;
        delete dummy;

        return ans;
    }
};
