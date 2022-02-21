/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
#include <cmath>

/**
 * 注意该链表没有Dummy Head
 * 
 */
class Solution
{
    ListNode *head;
public:
    Solution(ListNode *head)
    {
        this->head = head;
    }

    int getRandom()
    {
        int ans;
        ListNode *cur = head;
        for (int i = 1; ; i++) {
            if (std::rand() % i == 0) { // 我们认为 std::rand() % i == 0 的概率为 1/i
                ans = cur->val;
            }
            cur = cur->next;
            if (cur == nullptr) {
                break;
            }
        }
        return ans;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */