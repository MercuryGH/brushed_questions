#include <vector>
#include <algorithm>
using std::vector;

/**
 * 序列在左、中、右三段中，仅在左、右两段有序。
 */
class Solution
{
public:
    int findUnsortedSubarray(vector<int> &nums)
    {
        const int n = nums.size();
        if (n == 0 || n == 1) {
            return 0;
        }

        auto unsortedLeft = nums.end();
        auto unsortedRight = nums.end();
        for (auto itr = nums.begin() + 1; itr != nums.end(); itr++) {
            if (*itr < *(itr - 1)) {
                unsortedLeft = itr - 1;
                break;
            }
        }
        // 不使用反向迭代器，直接正向迭代
        for (auto itr = nums.end() - 2; itr != nums.begin() - 1; itr--) {
            if (*itr > *(itr + 1)) {
                unsortedRight = itr + 1;
                break;
            }
        }
        // 如果整个序列就是递增有序的
        if (unsortedLeft == nums.end() && unsortedRight == nums.end()) {
            return 0;
        }

        const auto minmax = std::minmax_element(unsortedLeft, unsortedRight + 1);
        const auto minElement = *minmax.first;
        const auto maxElement = *minmax.second;

        // 找到插入位置
        auto left = nums.begin();
        auto right = nums.end() - 1;
        for (auto itr = unsortedLeft; itr != nums.begin(); itr--) {
            if (minElement <= *itr && minElement >= *(itr - 1)) {
                left = itr;
                break;
            }
        }
        for (auto itr = unsortedRight; itr != nums.end() - 1; itr++) {
            if (maxElement >= *itr && maxElement <= *(itr + 1)) {
                right = itr;
                break;
            }
        }

        return right - left + 1;
    }
};