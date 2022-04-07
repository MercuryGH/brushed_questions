#include <algorithm>
#include <deque>
#include <map>
#include <queue>
#include <vector>
using std::vector;

class Solution
{
    struct MonoQueue
    {
        std::deque<int> q;
        void push_max(int v)
        {
            while (true)
            {
                if (q.empty())
                {
                    break;
                }

                if (q.back() < v) // 等于不行（）
                {
                    q.pop_back();
                }
                else
                {
                    break;
                }
            }
            q.push_back(v);
        }
        void push_min(int v)
        {
            while (true)
            {
                if (q.empty())
                {
                    break;
                }

                if (q.back() > v)
                {
                    q.pop_back();
                }
                else
                {
                    break;
                }
            }
            q.push_back(v);
        }
        int getMax()
        {
            return q.front();
        }
        void pop(int v)
        {
            if (q.empty())
            {
                return;
            }

            if (v == q.front())
            {
                q.pop_front();
            }
        }
    };

public:
    int longestSubarray(vector<int> &nums, int limit)
    {
        const int n = nums.size();
        MonoQueue maxQueue;
        MonoQueue minQueue;

        int l = 0;
        int r = 0;
        int ans = 0;
        while (true) {
            if (r >= n) {
                break;
            }
            maxQueue.push_max(nums[r]);
            minQueue.push_min(nums[r]);
            int diff = maxQueue.getMax() - minQueue.getMax();
            // const int windowSize = r - l + 1;
            while (diff > limit) {
                maxQueue.pop(nums[l]);
                minQueue.pop(nums[l]);
                diff = maxQueue.getMax() - minQueue.getMax();
                l++;
            }
            // std::cout << "Test\n";
            ans = std::max(ans, r - l + 1);

            r++;
        }
        return ans;
    }
};