# 最大正方形

给定一个$n \times m$的01矩阵$a_{n,m}$，请找出其中只包含$1$的最大正方形的面积。

## 暴力解

枚举$(i,j)$作为正方形的左上角起点，$l$作为正方形的长度，看区域内是否只含有$1$。时间复杂度是$O(nm \cdot \min(n, m)^2)$级别的，需要四重循环。

## DP解

这个DP的解法非常难想。

记$f_{i,j}$为以$(i,j)$作为右下角，所能得到的只包含$1$的最大正方形的边长。那么答案在$\max_{i,j} f_{i,j}$中。

考虑状态转移。先证明一个引理。

**引理**

设$(i,j), (i- 1, j -1)$都未越界。那么

$$
f_{i,j} \leq \min(f_{i,j-1}, f_{i-1,j}, f_{i-1, j - 1}) + 1
$$

且

$$
f_{i,j} \geq \min(f_{i,j-1}, f_{i-1,j}, f_{i-1, j - 1}) + 1
$$

**证明**

一方面，如果以$(i,j)$为右下角的，只包含$1$的正方形的最大边长为$f_{i,j}$，那么以$(i,j-1), (i-1,j), (i-1,j-1)$为右下角的正方形，至少可以获得一个边长为$f_{i,j} - 1$的只包含$1$的正方形。因此

$$
f_{i,j-1} \geq f_{i,j} - 1 \\
f_{i-1,j} \geq f_{i,j} - 1 \\
f_{i-1,j-1} \geq f_{i,j} - 1
$$

于是，证得$f_{i,j} \leq \min(f_{i,j-1}, f_{i-1,j}, f_{i-1, j - 1}) + 1$。

另一方面，在固定$f_{i,j-1}, f_{i-1,j}, f_{i-1,j-1}$的情况下：

* 若$a_{i,j} = 0$，则$f_{i,j} = 0$。
* 若$a_{i,j} = 1$，我们知道其左、上、左上三个方向的近邻点，所能形成的正方形公共区域的边长最大为$\min(f_{i,j-1}, f_{i-1,j}, f_{i-1,j-1})$。这个区域再加上$a_{i,j} = 1$，就能让以$(i,j)$为右下角的正方形获得 +1 边长，于是

$$
f_{i,j} \geq \min(f_{i,j-1}, f_{i-1,j}, f_{i-1, j - 1}) + 1
$$

证毕。

终于，我们推出了状态转移方程：

$$
f_{i,j} = \begin{cases}
a_{i,j}, &i = 0 \vee j = 0 \\
0, &a_{i, j} = 0 \\
\min(f_{i,j-1}, f_{i-1,j}, f_{i-1, j - 1}) + 1, & \text{otherwise}
\end{cases}.
$$