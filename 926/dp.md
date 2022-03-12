# 翻转字符

对任意01串$s_n$，如果存在某个$i \in [1,n]$，满足$i$的左侧均为$0$，右侧均为$1$，则我们称$s_n$是单调不减的。现给定$s_n$，你可以翻转其中的任意元素$s_i$（0变1或1变0），直到$s_n$变为单调不减为止。请给出翻转次数的最小值。

## DP解

记$f_i$表示$s_{1:i}$在$s_i$最终为$0$时，翻转次数的最小值；$g_i$表示$s_{1:i}$在$s_i$最终为$1$时，翻转次数的最小值，那么答案在$\min(f_n, g_n)$。状态转移方程如下：

$$
\begin{aligned}
f_i &= f_{i-1} + (s_i = 1), \\
g_i &= \min(f_{i-1}, g_{i-1}) + (s_i = 0)
\end{aligned}
$$

初始条件为$f_1 = (s_1 = 1), g_1 = (s_1 = 0)$。

```cpp
int minFlipsMonoIncr(string s)
{
    const int n = s.length();
    vector<int> dp1(n), dp2(n);
    dp1[0] = s[0] == '1';
    dp2[0] = s[0] == '0';

    for (int i = 1; i < n; i++) {
        dp1[i] = dp1[i - 1] + (s[i] == '1');
        dp2[i] = std::min(dp1[i - 1], dp2[i - 1]) + (s[i] == '0');
    }
    return std::min(dp1[n - 1], dp2[n - 1]);
}
```
