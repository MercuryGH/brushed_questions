# 序列和

给定正整数$n$，输出所有和为$n$的连续正整数序列。一个和为$n$的连续正整数序列是一个正整数集合$\{k, k+1, \dots, k+l\}$，满足

$$
\sum_{i=k}^{k+l} i = n.
$$

## 暴力解

从$\frac{n}{2}$开始枚举每个正整数$k$，作为和为$n$的连续正整数序列的起点。

对每个起点，枚举$k+1, k+2, \dots$并持续更新和，直到和等于$n$，则加入答案；否则和大于$k$，那么$k$不能作为和为$n$的连续正整数序列的起点。无论是否加入答案，下一个起点即为$k-1$。

这个算法的时间复杂度分析如下：

对于最坏情况$k=1$，由

$$
1 + 2 + \dots + l = \frac{l(l+1)}{2} = n
$$

知$l = O(\sqrt{n})$。由于枚举次数为$\frac{n}{2}$，故本算法的最坏时间复杂度为$O(n \sqrt n)$。

## 数学优化

等差数列求和居然用$O(\sqrt n)$，为什么不直接套公式呢……

对于首项为$k$，公差为$1$的等差数列，我们期望它的前$l$项和在恰好大于或等于$n$时停止求和。首先计算前$l$项和：

$$
S_l = \frac{l(a_1 + a_l)}{2} = \frac{l(k+k+l-1)}{2} = \frac{l(2k + l - 1)}{2}.
$$

令$S_l \geq n$，得

$$
l^2 + (2k - 1)l - 2n \geq 0
$$

我们希望得到使得正整数$l$最小的不等式的解。容易分析，等式在$l < 0$必然有一个解，因此我们只需关注$l > 0$的那个解。由求根公式

$$
l' = \frac{1-2k + \sqrt{(2k-1)^2 + 8n}}{2}.
$$

在求出$l'$后，取 `ceil`即可。这样就把时间复杂度优化到了为$O(n)$。

但是，上面的做法可能存在精度问题。于是，我们可以想出如下的方案：如果$l'$恰好是正整数，那么答案+1，否则$k$不能作为和为$n$的连续正整数序列的起点。要判断$l'$是正整数，只需要判断 `sqrt()`结果是否为正整数，且分子结果是否为偶数即可。

另外还需要注意的是，小心计算$\Delta$的时候爆int。

```cpp
class Solution
{
    bool isSquare(long long num)
    {
        long long sqrtNum = std::sqrt(num);
        return sqrtNum * sqrtNum == num;
    }
    bool isOdd(long long num)
    {
        return num % 2 == 1;
    }
public:
    vector<vector<int>> findContinuousSequence(int target)
    {
        vector<vector<int>> ans;
        for (long long k = 1; k <= target / 2; k++)
        {
            const long long delta = (2 * k - 1) * (2 * k - 1) + 8 * target;
            if (isSquare(delta) == false)
            {
                continue;
            }
            const long long nominator = 1 - 2 * k + std::sqrt(delta);
            if (isOdd(nominator))
            {
                continue;
            }
            const long long l = nominator / 2;

            const int sum = l * (2 * k + l - 1) / 2;
            if (sum == target)
            {
                vector<int> curAns;
                for (int i = k; i < k + l; i++)
                {
                    curAns.push_back(i);
                }
                ans.push_back(curAns);
            }
        }
        return ans;
    }
};
```
