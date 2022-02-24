struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/**
 * 排序链表。排序算法可自定义
 * 经典，建议背诵
 */
class Solution
{
    /**
     * 链表插入排序
     * 
     * 附：二分插入排序的平均时间复杂度还是 O(n^2)。
     * 数组适合二分，但不适合插入；链表适合插入，但不适合二分。所以二分插入排序十分尴尬。
     */
    ListNode *insertionSortList(ListNode *head) {
        if (head == nullptr) {
            return nullptr;
        }
        ListNode *dummyHead = new ListNode(0);
        dummyHead->next = head;

        ListNode *lastSorted = head;  // 待排序结点的前一个结点
        ListNode *toBeSorted = head->next;  // 待排序结点
        while (true) {
            if (toBeSorted == nullptr) {
                break;
            }

            if (lastSorted->val <= toBeSorted->val) {  // 有序
                lastSorted = lastSorted->next;  // 下一个
            } else {
                ListNode *prev = dummyHead;  // 不有序，从头开始找插入结点
                while (prev->next->val <= toBeSorted->val) {
                    prev = prev->next;
                }
                // prev 已经定位了待插入的地点（链表没法二分）
                lastSorted->next = toBeSorted->next;
                toBeSorted->next = prev->next;
                prev->next = toBeSorted;
            }
            toBeSorted = lastSorted->next;
        }
        return dummyHead->next;
    }

    /**
     * 链表归并排序
     */

    ListNode *mergeSortList(ListNode *head) {
        return divide(head);
    }

    ListNode *divide(ListNode *head) { 
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        ListNode *slowPrev;
        ListNode *slow = head;
        ListNode *fast = head;
        while (true) {  // 让 slowPrev 恰好在链表的中间，fast恰好在链表的末尾
            if (fast == nullptr || fast->next == nullptr) {
                break;
            }

            slowPrev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        slowPrev->next = nullptr;  // 断链！！！
        // 理解该代码的最好方式：画奇数和偶数的情况图
        ListNode *mid = slow;

        return merge(divide(head), divide(mid));
    }
    ListNode *merge(ListNode *head1, ListNode *head2) {
        ListNode *dummyHead = new ListNode(0);
        ListNode *cur = dummyHead;
        ListNode *cur1 = head1;
        ListNode *cur2 = head2;
        while (true) {
            if (cur1 == nullptr || cur2 == nullptr) {
                break;
            }

            if (cur1->val <= cur2->val) {
                cur->next = cur1;
                cur1 = cur1->next;
            } else {
                cur->next = cur2;
                cur2 = cur2->next;
            }
            cur = cur->next;
        }
        if (cur1 != nullptr) {
            cur->next = cur1;
        }
        if (cur2 != nullptr) {
            cur->next = cur2;
        }
        ListNode *ret = dummyHead->next;
        delete dummyHead;
        return ret;
    }

public:
    ListNode *sortList(ListNode *head)
    {
        return mergeSortList(head);
    }
};