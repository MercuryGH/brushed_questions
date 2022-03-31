# 最长回文子序列

给定字符串$s$，长度为$n$，找出它的最长回文子序列（LPS）。

注意，“序列”与“串”的含义不同。

## DP解

记$f_{i,j}$为$s_{i:j}$的最长回文子序列的长度，则答案在$f_{1,n}$。

可见这也是一个区间DP。状态转移如下：

$$
f_{i,j} = \begin{cases}
f_{i+1, j -1} + 2, &j - i \geq 2 \wedge s_i = s_j  \\
\max(f_{i+1, j}, f_{i,j-1}), &j - i \geq 1 \wedge s_i \neq s_j \\
2, &j - i = 1 \wedge s_i = s_j \\
1, &j - i = 0
\end{cases}.
$$
