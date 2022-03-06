/**
 * 数据结构模拟题
 */

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
using std::vector, std::string;

struct ListNode;
std::unordered_map<string, ListNode *> addrMap;
struct ListNode {
    int val;
    string addr;
    string nextAddr;
    ListNode(): val(0), addr("-1"), nextAddr("-1") {}
    ListNode(int val, string addr, string nextAddr): val(val), addr(addr), nextAddr(nextAddr) {}
    void printAll() {
        for (ListNode *cur = this; cur; cur = addrMap[cur->nextAddr]) {
            std::cout << cur->val << " ";
        }
        std::cout << "\n";
    }
    void printFormat() {
        for (ListNode *cur = this; cur; cur = addrMap[cur->nextAddr]) {
            std::cout << cur->addr << " " << cur->val << " " << cur->nextAddr;
            std::cout << "\n";
        }
    }
};

std::unordered_set<int> scannedVal;
ListNode *removeDuplication(ListNode *head) {
    ListNode *prev = new ListNode();
    prev->nextAddr = head->addr;

    ListNode *lastRemoved = new ListNode();
    ListNode *removedListHead = lastRemoved;
    for (ListNode *cur = head; cur; ) {
        if (scannedVal.find(cur->val) == scannedVal.end() && scannedVal.find(-cur->val) == scannedVal.end()) {
            scannedVal.insert(cur->val);
            prev = addrMap[prev->nextAddr];
            cur = addrMap[cur->nextAddr];
        } else { // remove
            string tmpAddr = cur->nextAddr;

            prev->nextAddr = cur->nextAddr;
            cur->nextAddr = "-1";
            lastRemoved->nextAddr = cur->addr;
            lastRemoved = cur;

            cur = addrMap[tmpAddr];
        }
    }
    return addrMap[removedListHead->nextAddr];
}

int main() {
    freopen("testdata.in", "r", stdin);

    int n;
    string headAddr;
    std::cin >> headAddr >> n;

    addrMap["-1"] = nullptr;
    for (int i = 0; i < n; i++) {
        string addr;
        int val;
        string nextAddr;
        std::cin >> addr >> val >> nextAddr;

        ListNode *curNode = new ListNode(val, addr, nextAddr);
        addrMap[addr] = curNode;
    }

    ListNode *headNode = addrMap[headAddr];
    ListNode *removedListHead = removeDuplication(headNode);
    headNode->printFormat();
    if (removedListHead != nullptr) {
        removedListHead->printFormat();
    }

    return 0;
}
