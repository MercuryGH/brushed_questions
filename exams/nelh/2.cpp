#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <vector>
using std::vector, std::string;

struct Card {
    // enum Type {
    //     A, B, C, D, E
    // };

    int num; // 1 ~ 10
    char type;
    Card(int num, char c): num(num), type(c) {}
};

int getMostSeqNum(const vector<Card> &cards) {
    std::unordered_set<int> cardNums;
    for (const auto &card : cards) {
        cardNums.insert(card.num);
    }

    int maxSeq = 1;
    for (const int cardNum : cardNums) {
        for (int i = 1; ; i++) {
            if (cardNums.find(cardNum + i) != cardNums.end()) {
                maxSeq = std::max(maxSeq, i + 1);
            } else {
                break;
            }
        }
    }
    return maxSeq;
}

int getMostSameNum(const vector<Card> &cards) {
    std::unordered_map<int, int> numFreq;
    for (const auto &card : cards) {
        numFreq[card.num]++;
    }

    int ans = 1;
    for (const auto [k, v] : numFreq) {
        ans = std::max(ans, v);
    }
    return ans;
}

int getMostSameType(const vector<Card> &cards) {
    std::unordered_map<char, int> typeFreq;
    for (const auto &card : cards) {
        typeFreq[card.type]++;
    }

    int ans = 1;
    for (const auto [k, v] : typeFreq) {
        ans = std::max(ans, v);
    }
    return ans;
}

int findNumPairs(const vector<Card> &cards) {
    std::unordered_map<int, int> numFreq;
    for (const auto &card : cards) {
        numFreq[card.num]++;
    }

    int flag = 0;
    for (const auto [key, value] : numFreq) {
        if (value == 2) {
            flag++;
        }
    }

    return flag;
}

/*
 * 15000: 5 same number
 * 8000: 5 same type && 5 seq num
 * 300: 5 same type
 * 150: 4 same num
 * 40: 三带二
 * 20: 5 seq num
 * 6: 3 same num
 * 4: 两对
 * 2: 一对
 */
int judge(vector<Card> &cards) {
    const int seq = getMostSeqNum(cards);
    const int sameNum = getMostSameNum(cards);
    const int sameType = getMostSameType(cards);
    const int pairs = findNumPairs(cards);
    if (sameNum == 5) {
        return 15000;
    }
    if (sameType == 5 && seq == 5) {
        return 8000;
    }
    if (sameType == 5) {
        return 300;
    }
    if (sameNum == 4) {
        return 150;
    }
    if (sameNum == 3 && pairs == 1) {
        return 40;
    }
    if (seq == 5) {
        return 20;
    }
    if (sameNum == 3) {
        return 6;
    }
    if (pairs == 2) {
        return 4;
    }
    if (pairs == 1) {
        return 2;
    }
    return 1;
}

int main()
{
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        int nums[10];
        char types[10];
        for (int i = 0; i < n; i++) {
            std::cin >> nums[i];
        }
        for (int i = 0; i < n; i++) {
            std::cin >> types[i];
        }
        vector<Card> cards;
        for (int i = 0; i < n; i++) {
            cards.emplace_back(nums[i], types[i]);
        }

        std::cout << judge(cards) << "\n";
    }

    return 0;
}