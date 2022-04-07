# 最长公共子序列

给定字符串$s,t$，长度分别为$n,m$，找出它们的最长公共子序列（LCS）。

注意，“序列”与“串”的含义不同。

## DP解

记$f_{i,j}$为$s_{1:i}$和$t_{1:j}$的最长公共子序列的长度，则答案在$f_{n,m}$。

状态转移考虑如下：

* 当$s_i = t_j$时，直接有$f_{i,j} = f_{i-1, j - 1} + 1$；
* 当$s_i \neq t_j$时，由于$f_{i,j}$关于其中一维的单调性，有$f_{i,j} = \max(f_{i-1,j}, f_{i, j-1})$。

初值条件为$f_{i, 0 } = f_{0, j} = 0$。