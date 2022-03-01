# 分割等和子集

给定序列$a_n$，请判断是否存在若干下标两两不同的元素$a_{i_1}, \dots, a_{i_k}$，满足$a_{i_1} + \dots + a_{i_k} = \sum_{i=1}^n a_i $。

## DP解

记$S = \sum_{i=1}^n a_i$。若$S$为奇数，必然不存在分割等和子集的方案。

若$S$为偶数，考虑动态规划。

记$f_{i,j}$表示只考虑子序列$a_{1:i}$，存在满足$a_{i_1} + \dots + a_{i_k} = j $的方案，则答案在$f_{i, S / 2}$。且状态转移方程为

$$
f_{i,j} = \begin{cases} 
f_{i-1,j} \vee f_{i-1,j-a_i} &, j \geq a_i  \\
f_{i-1,j} &, j < a_i
 \end{cases}.
$$

初值条件为$f_{i,0}=1$，且$f_{1,a_1}=1$，$\forall j \in (0, a_1), f_{1,j} = 0$。