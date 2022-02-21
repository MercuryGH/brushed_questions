#include <vector>

/**
 * 超出半数的众数问题，有经典非哈希的 O(n) 算法（摩尔投票）
 * 但其他算法也很精彩，详见官方题解
 */
class Solution {
public:
    int majorityElement(std::vector<int>& nums) {
        int candidate = -1;
        int count = 0;

        for (const int num : nums) {
            if (num == candidate) {
                count++;  // 被支持
                continue;
            }

            count--;  // 没被支持，对消
            if (count < 0) {  // 对消完了，没有筹码
                candidate = num;  // 换个人
                count = 1;  // 该人的支持为1
            }
        }
        return candidate;
    }
};