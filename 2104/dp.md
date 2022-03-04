# 子序列极差之和

给定序列$a_n$，请计算

$$
\sum_{1 \leq i \leq j \leq n} (\max_{i\leq k \leq j }(a_k) - \min_{i\leq k \leq j }(a_k)).
$$

## 暴力解

考虑枚举$(i,j)$，然后在$a_{i:j}$内$O(n)$扫描最大值和最小值，得到极差。时间复杂度为$O(n^3)$，很暴力。

## DP解

考虑区间DP，记$f_{i,j}$为$a_{i:j}$的最大值，$g_{i,j}$为$a_{i:j}$的最小值。那么$f$的状态转移方程为

$$
f_{i,j} = \begin{cases}
a_i, & j = i \\
\max(a_i, a_j), & j - i = 1, \\
\max(f_{i+1,j},f_{i, j -1}, a_i, a_j), & j - i \geq 2
\end{cases}
$$

$g$的状态转移方程只是把$\max$换成了$\min$。

### DP方程太臃肿了

重写：

$$
f_{i,j} = \begin{cases}
a_i, & j = i \\
\max(f_{i, j - 1},a_{j}), & j - i \geq 1, \\
\end{cases}
$$

这样就够了。

最终答案在$\sum_{1 \leq i \leq j \leq n}(f_{i,j} - g_{i,j})$中。

时间复杂度为$O(n^2)$。

### DP优化

注意到无论是$f$还是$g$都只依赖前一个$(i,j-1)$的状态，且该状态只会被用作递推一次，所以我们完全可以改变枚举策略——先 `i = 1 to n`，然后 `j = i to n`，即可推遍这个优化后的状态转移方程。

（这样做的话，就不是区间DP了，因此不再需要从 `len`开始枚举）

如此，$f$和$g$的空间都可以减为$O(1)$。

```cpp
long long subArrayRanges(vector<int>& nums) {
    const int n = nums.size();

    long long ans = 0;
    int f = 0;
    int g = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (j == i) {
                f = nums[i];
                g = nums[i];
            } else {
                f = std::max(f, nums[j]);
                g = std::min(g, nums[j]);
                ans += (f - g);
            }
        }
    }
    return ans;
}
```
