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
#include <unordered_set>
#include <vector>
using std::vector, std::string;

/**
 * DP 时间复杂度 O(nk)，滑动窗口时间复杂度 O(n)
 * 
 * 重点：题意转换。把「最多可以把 K 个 0 变成 1，求仅包含 1 的最长子数组的长度」
 * 转换为 「找出一个最长的子数组，该子数组内最多允许有 K 个 0 」。
 */
class Solution
{
public:
    int longestOnes(vector<int> &nums, int k)
    {
        const int n = nums.size();
        int l = 0;
        int r = 0;
        int ans = 0;
        int windowZeroNum = 0;
        while (true) {
            if (r >= n) {
                break;
            }
            if (nums[r] == 0) {
                windowZeroNum++;
            }
            if (windowZeroNum > k) {
                while (true) {
                    if (nums[l] == 0) {
                        windowZeroNum--;
                    }
                    l++;
                    if (windowZeroNum == k) {
                        break;
                    }
                }
            }

            ans = std::max(ans, r - l + 1);
            r++;
        }
        return ans;
    }
};

