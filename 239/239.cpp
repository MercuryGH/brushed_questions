#include <algorithm>
#include <deque>
#include <map>
#include <queue>
#include <vector>
using std::vector;

/**
 * 滑动窗口最大值
 */
class Solution
{
    /**
     * 单调队列做法
     */
    struct MonotonicQueue
    {
        std::deque<int> deq;
        void push(int element)
        {
            while (deq.empty() == false && deq.back() < element)
            {
                deq.pop_back();
            }
            deq.push_back(element);
        }

        int max() { return deq.front(); }

        void pop(int element)
        {
            if (deq.empty() == false && deq.front() == element)
            {
                deq.pop_front();
            }
        }
    };
    vector<int> maxSlidingWindowMonoDeque(vector<int> &nums, int k)
    {
        const int n = nums.size();
        MonotonicQueue window;
        vector<int> res;
        for (int i = 0; i < n; i++)
        {
            if (i < k - 1)
            { //先填满窗口的前 k - 1
                window.push(nums[i]);
            }
            else
            { // 窗口向前滑动
                window.push(nums[i]);
                res.push_back(window.max());
                window.pop(nums[i - k + 1]);
            }
        }
        return res;
    }

    /**
     * STL map 做法
     */
    vector<int> maxSlidingWindowRbTree(vector<int> &nums, int k)
    {
        const int n = nums.size();
        std::map<int, int> treemap;
        for (int i = 0; i < k; i++)
        {
            treemap[nums[i]]++;
        }

        vector<int> ans;
        for (int r = k, l = 0;; r++, l++)
        {
            ans.push_back(treemap.rbegin()->first); // 注意不能用end
            if (treemap[nums[l]] == 1)
            { // 注意区分 erase 和 set to zero
                treemap.erase(nums[l]);
            }
            else
            {
                treemap[nums[l]]--;
            }

            if (r == n)
            { // 不太优雅
                break;
            }

            treemap[nums[r]]++;
        }
        return ans;
    }

public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        return maxSlidingWindowMonoDeque(nums, k);
    }
};
