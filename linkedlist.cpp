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
            // getchar();
        }
        std::cout << "\n";
    }
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
     * 两个返回值：小链表的头和大链表的头
     */
    void getPartition(ListNode *pivot, ListNode *&lessHead, ListNode *&greaterHead) {
        ListNode *const lessDummyHead = new ListNode(0, nullptr);
        ListNode *const greaterDummyHead = new ListNode(0, nullptr);
        ListNode *less = lessDummyHead;
        ListNode *greater = greaterDummyHead;

        for (ListNode *cur = pivot->next; cur; cur = cur->next) {
            if (cur->val <= pivot->val) {
                less->next = cur; // 接小链表
                less = less->next;
            } else {
                greater->next = cur; // 接大链表
                greater = greater->next;
            }
        }
        // 断链！！
        less->next = nullptr;
        greater->next = nullptr;

        lessHead = lessDummyHead->next;
        greaterHead = greaterDummyHead->next;
        delete lessDummyHead;
        delete greaterDummyHead;
    }

    /**
     * 链表快速排序
     * 时间复杂度 n log n，空间复杂度 log n
     * 
     * pivot 如果还像随机化快速排序那样选择任一元素，就可能要遍历整个链表，代价太大
     * 因此这里只实现了选择头元素作为pivot
     * 过不了 Leetcode 的 worst case
     */
    ListNode *quickSortList(ListNode *head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode *lessHead;
        ListNode *greaterHead;

        ListNode *const pivot = head;
        getPartition(pivot, lessHead, greaterHead);

        lessHead = quickSortList(lessHead);
        greaterHead = quickSortList(greaterHead);

        // 把 less pivot greater 串起来
        if (lessHead == nullptr) {
            pivot->next = greaterHead;
            return pivot;
        }
        ListNode *cur = lessHead;
        while (cur->next) {
            cur = cur->next;
        }
        cur->next = pivot;
        pivot->next = greaterHead;

        return lessHead;
    }

    /**
     * 链表归并排序（递归版）
     * 时间复杂度 n log n 空间复杂度 log n
     * 如果使用迭代的归并排序，则可以做到时间复杂度 n log n，空间复杂度 1
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
        // return mergeSortList(head);
        return quickSortList(head);
    }
};

int main() {
    int a[] = {4,19,14,5,-3,1,8,5,11,15};
    ListNode *listNodes[10];
    for (int i = 0; i < 10; i++) {
        ListNode *listNode = new ListNode(a[i]);
        listNodes[i] = listNode;
    }

    for (int i = 0; i < 9; i++) {
        listNodes[i]->next = listNodes[i + 1];
    }
    listNodes[9]->next = nullptr;

    Solution s;
    s.sortList(listNodes[0])->printAll();

    return 0;
}