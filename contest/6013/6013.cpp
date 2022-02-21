#include <iostream>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
    void printAll() {
        for (ListNode *cur = this; cur; cur = cur->next) {
            std::cout << cur->val << " ";
        }
        std::cout << "\n";
    }
};

class Solution
{
public:
    ListNode *mergeNodes(ListNode *head)
    {
        ListNode *cur = head->next;
        while (true)
        {
            int sum = cur->val;
            ListNode *nxt = cur->next;
            for (; nxt->val != 0; nxt = nxt->next)
            {
                sum += nxt->val;
            }
            cur->val = sum;
            cur->next = nxt->next;

            if (cur->next == nullptr)
            {
                break;
            }
            cur = cur->next;
        }
        return head->next;
    }
};

int main()
{
    ListNode *listNodes[10];
    int vals[10] = {0, 3, 1, 0, 4, 5, 2, 0};
    for (int i = 0; i < 8; i++)
    {
        ListNode *l = new ListNode(vals[i]);
        listNodes[i] = l;
    }
    for (int i = 0; i < 7; i++) {
        listNodes[i]->next = listNodes[i + 1];
    }
    listNodes[7]->next = nullptr;

    listNodes[0]->printAll();
    return 0;
}