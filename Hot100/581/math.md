# 最短无序连续子数组

给定序列$a_n$，请找出最短的子序列$a_{i:j}$（两端闭区间），使得如果对这个子序列进行升序排序，那么整个序列也会变成升序排序。

## 解答

暴力解：整体排序后，一一对比，即可找出最短的$a_{i:j}$。时间复杂度为$O(n \log n)$。

下面我们用数学方法（数学证明）找出一个$O(n)$的解。

既然要找出最短的$a_{i:j}$，那么就要找出$a_i, a_j$，即$i, j$。证明一个引理：

**引理1**

如果$a_i, a_j$能成为最短的$a_{i:j}$的端点元素，那么必然有

$$
a_i > \min(a_{i:n}) \geq a_{i-1} \geq \dots \geq a_1 \\
a_j < \max(a_{1:j}) \leq a_{j+1} \leq \dots \leq a_n
$$

证明：只需证$a_i > \min(a_{i:n}) \geq a_{i-1}$。

先证明$a_i > \min(a_{i:n})$。首先由$\min$的性质，必然有$a_i \geq \min(a_{i:n})$，于是只需证$a_i \neq \min(a_{i:n})$。反证：若不然，则$a_i = \min(a_{i:n})$，那么最短的子序列至少可以是$a_{i+1:j}$，与假设矛盾。

然后证明$\min(a_{i:n}) \geq a_{i - 1}$。由于$a_n$升序排序后，$\min(a_{i:n})$显然不变，故该式必然成立。注意：该式能取等，是因为相邻元素不一定严格递增/减，可能相等。

证毕（第二行的不等式由对称性易得）。

注意到引理给出的不等式并不能够完全确定$i$和$j$的位置，因为可能存在多个$i, j$满足以上不等式，也可能根本不存在这样的$i, j$。因此，我们来证明下一个引理。

**引理2**

若不存在$i,j$满足以上不等式，则整个序列必然是升序有序的。

证明：略。

**引理3**

若存在多个$i, j$满足以上不等式，则最终答案是最小的$i$和最大的$j$。

证明：略。

**思路**

有了引理，我们只要枚举两次，第一次从$n$到$1$枚举，找出满足

$$
a_i > \min(a_{i:n}) \geq a_{i-1}
$$

的$i$，且用较小的$i$覆盖较大的$i$；第二次从$1$到$n$枚举，找出$j$即可。时间复杂度显然为$O(n)$。

**代码**

```cpp
int findUnsortedSubarray(vector<int> &nums)
{
    const int n = nums.size();
    if (n == 0 || n == 1) {
        return 0;
    }

    int minElement = nums[n - 1];
    int maxElement = nums[0];
    int l = -1;
    int r = -1;
    for (int i = n - 1; i >= 1; i--) {
        if (nums[i] > minElement && minElement >= nums[i - 1]) {
            l = i;
        }
        minElement = std::min(minElement, nums[i]);
    }
    if (nums[0] > minElement) {
        l = 0;
    }

    for (int i = 0; i < n - 1; i++) {
        if (nums[i] < maxElement && maxElement <= nums[i + 1]) {
            r = i;
        }
        maxElement = std::max(maxElement, nums[i]);
    }
    if (nums[n - 1] < maxElement) {
        r = n - 1;
    }

    if (l == -1 && r == -1) {
        return 0;
    }
    return r - l + 1;
}
```

## 解答

你一定看不懂那个数学方法。因为证明太过于繁琐，只能靠蒙来理解。

下面给出一个很直观的$O(n)$算法思想：

1. 首先，从前往后找有序序列，从后往前找有序序列，一共可以找到两个有序序列。
2. 分别在剩余非有序序列中，找最小值和最大值。
3. 在前面的有序序列中，找到最小值可以插入的位置；在后面的有序序列中，找到最大值可以插入的位置。
4. 需要重新排序的部分，就是这两个可以插入的位置之间的部分。

[1627957087-VYaluV-最短无序连续子数组题解.png (2077×1205) (leetcode-cn.com)](https://pic.leetcode-cn.com/1627957087-VYaluV-%E6%9C%80%E7%9F%AD%E6%97%A0%E5%BA%8F%E8%BF%9E%E7%BB%AD%E5%AD%90%E6%95%B0%E7%BB%84%E9%A2%98%E8%A7%A3.png)

实际细节很多，一次性写对有难度。

```cpp
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
```
