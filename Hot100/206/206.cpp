struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/**
 * 反转链表
 */
class Solution
{
public:
    /**
     * 错误写法，因为给dummy赋 nullptr 不等于给 head->next 赋 nullptr，所以出现了内存越界访问
     */
    ListNode *reverseListBad(ListNode *head)
    {
        ListNode *dummy = new ListNode(-1);
        dummy->next = head;

        ListNode *prev = dummy;
        ListNode *cur = head;
        while (true)
        {
            ListNode *tmp = cur->next;
            cur->next = prev;

            if (tmp == nullptr)
            {
                break;
            }
            prev = cur;
            cur = tmp;
        }
        delete dummy;
        dummy = nullptr;

        return cur;
    }

    /**
     * 错误写法2，犯的错误与1一样
     */
    ListNode *reverseListBad2(ListNode *head)
    {
        ListNode *prev = nullptr;
        ListNode *cur = head;
        while (true)
        {
            ListNode *tmp = cur->next; // 取出tmp并视其为 ListNode * 的行为已经很危险了，该句可能报错
            cur->next = prev;

            if (tmp == nullptr)
            {
                return cur;
            }
            prev = cur;
            cur = tmp;
        }
    }

    ListNode *reverseList(ListNode *head)
    {
        ListNode *prev = nullptr;
        ListNode *cur = head;
        while (true)
        {
            if (cur == nullptr)
            {
                return prev;
            }
            ListNode *tmp = cur->next;
            cur->next = prev;

            prev = cur;
            cur = tmp;
        }
    }
};