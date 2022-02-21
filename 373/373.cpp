#include <vector>
#include <queue>
#include <algorithm>

/**
 * 多路归并
 * 重点是 priority_queue 的 Modern 使用方式
 */
class Solution
{
public:
    std::vector<std::vector<int>> kSmallestPairs(std::vector<int> &nums1, std::vector<int> &nums2, int k)
    {
        std::vector<std::vector<int>> pairs;
        int n = nums1.size();
        int m = nums2.size();
        bool noSwap = true;

        if (n > m)
        {
            noSwap = false;
            std::swap(nums1, nums2);
            std::swap(n, m);
        }  // 保证 n <= m

        const auto cmp = [&](const auto &a, const auto &b)
        {
            return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second];
        }; // [&]表示要截取外部作用域中的变量，且用引用方式截取。这里截取的就是nums1和nums2

        std::priority_queue<
            std::pair<int, int>,              // 里面装的元素类型
            std::vector<std::pair<int, int>>, // 基本上固定为vector<里面装的元素类型>
            decltype(cmp)                     // 用于比较的lambda表达式类型。如果 greater 返回 true，则为小根堆
        > q(cmp); // 如果使用了lambda，这里的格式就是 "变量名(lambda名)"

        for (int i = 0; i < std::min(n, k); i++)
        {
            q.push({i, 0});  // 这里不是线性建堆。如果线性建堆，还能更快
            // 但由于下面的操作也需要 O(n log n) 的时间，所以这里优化成 O(n) 对算法整体复杂度基本没有影响
        }

        while (q.empty() == false && pairs.size() < k)
        {
            const auto [a, b] = q.top();  // 还有这种语法糖？香
            const int element1 = nums1[a];
            const int element2 = nums2[b];
            q.pop();

            if (noSwap == true)
            {
                pairs.push_back({element1, element2});
            }
            else
            {
                pairs.push_back({element2, element1});
            }

            if (b + 1 < m)
            {
                q.push({a, b + 1});
            }
        }

        return pairs;
    }
};