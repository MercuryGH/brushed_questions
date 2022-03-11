#include <vector>
using std::vector;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/**
 * 合并 k 个升序链表
 * 思想：链表归并排序的 bottom-up 过程
 */
class Solution
{
    ListNode *merge(ListNode *head1, ListNode *head2)
    {
        ListNode *dummyHead = new ListNode(0);
        ListNode *cur = dummyHead;
        ListNode *cur1 = head1;
        ListNode *cur2 = head2;
        while (true)
        {
            if (cur1 == nullptr || cur2 == nullptr)
            {
                break;
            }

            if (cur1->val <= cur2->val)
            {
                cur->next = cur1;
                cur1 = cur1->next;
            }
            else
            {
                cur->next = cur2;
                cur2 = cur2->next;
            }
            cur = cur->next;
        }
        if (cur1 != nullptr)
        {
            cur->next = cur1;
        }
        if (cur2 != nullptr)
        {
            cur->next = cur2;
        }
        ListNode *ret = dummyHead->next;
        delete dummyHead;
        return ret;
    }

    ListNode *divide(const vector<ListNode *> &lists, const int l, const int r)
    {
        if (l == r)
        {
            return lists[l];
        }
        if (l > r)
        {
            return nullptr;
        }
        const int mid = (l + r) / 2;
        return merge(divide(lists, l, mid), divide(lists, mid + 1, r));
    }

public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        const int k = lists.size();
        return divide(lists, 0, k - 1);
    }
};