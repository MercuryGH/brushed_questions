struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/**
 * 判断两个相交链表的第一个交点
 * 暴力做法：遍历第一个链表，把节点存在一个 Set 里，然后遍历第二个链表，查当前节点是否在那个 Set 里面
 * 
 * 正确做法：双指针（非常巧妙的加法交换律，看Leetcode题解就能理解）
 */
class Solution
{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        ListNode *curA = headA;
        ListNode *curB = headB;
        while (true) {
            if (curA == curB) {
                return curA;
            }

            curA = (curA != nullptr) ? curA->next : headB;
            curB = (curB != nullptr) ? curB->next : headA;
        }
    }
};