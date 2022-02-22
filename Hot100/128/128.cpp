#include <vector>
#include <unordered_set>
using std::vector;

/**
 * 找出最长连续序列
 * 有O(n^2)朴素暴力和O(n log n)排序后暴力
 * 
 * 1. 第一个容易想到的 O(n) 时间算法：哈希集合，仅从连续序列开头开始找
 */
class Solution
{
public:
    int longestConsecutive(vector<int> &nums)
    {
        std::unordered_set<int> numSet;
        for (const int num : nums) {
            numSet.insert(num);
        }

        int ans = 0;
        for (const int num : numSet) {
            if (numSet.find(num - 1) == numSet.end()) {  // 没有前驱
                int curLen = 1;
                int curNum = num;
                while (numSet.find(curNum + 1) != numSet.end()) {
                    curNum++;
                    curLen++;
                }
                ans = std::max(ans, curLen);
            }
        }
        return ans;
    }
};