#include <vector>
#include <algorithm>

/**
 * 煎饼翻转。
 * 可以证明，每次让最大元素放到数组最右侧的未有序位置是一个策略。该策略可分为两步：
 * 1. 找到最大元素的下标，然后让它翻转到数组的起始位置；
 * 2. 做等同于数组长度的翻转。
 */
class Solution
{
public:
    std::vector<int> pancakeSort(std::vector<int> &arr)
    {
        std::vector<int> ans;
        const int n = arr.size();
        for (int i = n; i > 1; i--) {  // i 追踪数组最右侧的未有序位置
            int maxElementIndex = std::max_element(arr.begin(), arr.begin() + i) - arr.begin();
            if (maxElementIndex == i - 1) {  // 如果最大元素已经在它的位置上，就不用再做重复操作
                continue;
            }
            std::reverse(arr.begin(), arr.begin() + maxElementIndex + 1);
            ans.push_back(maxElementIndex + 1);
            std::reverse(arr.begin(), arr.begin() + i);
            ans.push_back(i);
        }
        return ans;
    }
};
