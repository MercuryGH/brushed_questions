#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::vector, std::string;

class Solution
{
    int n;
    // O(n) test if split to <= mid is OK.
    bool check(const vector<int> &nums, const int mid, const int m) {
        int curSum = 0;
        int segmentCnt = 0;
        for (int i = 0; i < n; i++) {
            if (curSum + nums[i] <= mid) {
                curSum += nums[i];
            } else {
                curSum = nums[i];
                segmentCnt++;
            }
        }
        segmentCnt++;
        return segmentCnt <= m;
    }
public:
    int splitArray(vector<int> &nums, int m)
    {
        n = nums.size();
        const int sum = std::accumulate(nums.begin(), nums.end(), 0);
        const int max = *std::max_element(nums.begin(), nums.end());

        int ans = 0;
        int l = max;
        int r = sum;
        while (true) {
            if (l > r) {
                break;
            }
            const int mid = (l + r) / 2;
            if (check(nums, mid, m)) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }
};