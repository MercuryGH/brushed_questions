# 解码方法

Suppose that a string of English letters is encoded into a string of numbers. To be more specific, `A`-`Z` are encoded into `0`-`25`. Since it is not a prefix code, the decoded result may not be unique. For example, `1213407` can be decoded as `BCBDEAH`, `MBDEAH`, `BCNEAH`, `BVDEAH` or `MNEAH`. Note that `07` is not `7`, hence cannot be decoded as `H`.

Given a string $s_n$, please find out the number of ways it can be decoded.

## DP解

第一次在ADS上做这道题，答案用的是倒序DP。

记$f_i$为$s_{i:n}$可被编码的数目，则最终答案在$f_1$中。初始条件$f_{n} = 1$。我们考虑另一个初始条件$f_{n-1}$：

* 若$s_{n-1} = \text{'1'}$，那么最后两个字符可以被拆分成$\{s_{n-1}\}, \{s_n\}$，或者直接合并成$\{s_{n-1}s_n\}$，二者均可译码，故$f_{n-2}=2$。
* 或者$s_{n-1} = \text{'2'}$且$s_{n} < \text{'6'}$，同上有$f_{n-2}=2$，
* 否则，$f_{n-1} = 1$。

考虑状态转移方程：

* 若$s_i = \text{'1'}$，或者$s_i = \text{'2'}$且$s_{i+1}<\text{'6'}$，那么$s_i$可以如下参与编码：

  * $\{s_i\}$，在这种情况下，每一个$f_{i+1}$的方案都是合法的，有$f_{i} = f_{i + 1}$；
  * $\{s_i s_{i+1}\}$，在这种情况下，每一个$f_{i+2}$的方案都是合法的，$f_i = f_{i + 2}$。
    因此$f_i = f_{i+1} + f_{i+2}$。
* 否则，$s_i$无法参与$\{s_i s_{i+1}\}$这种编码，只有$f_i = f_{i+1}$。

综上，状态转移方程如下：

$$
f_i = 
\begin{cases}
f_{i+1} + f_{i+2}, & s_i = \text{'1'} \vee (s_i = \text{'2'} \wedge s_{i+1} < \text{'6'}) \\
f_{i+1}, & \text{otherwise}
\end{cases}
$$

# 改版题目

现在，`A`-`Z` are encoded into `1`-`26`。注意单独的 `0`无法被编码。如何修改状态转移方程？

答：

$$
f_i = 
\begin{cases}
f_{i+1} + f_{i+2}, & s_i = \text{'1'} \vee (s_i = \text{'2'} \wedge s_{i+1} \leq \text{'6'}) \\
0, & s_i = \text{'0'} \\
f_{i+1}, & \text{otherwise} 
\end{cases}
$$

初始条件为$f_n = (s_n \neq 0)$，

$$
f_{n-1}=
\begin{cases}
f_{n} + 1, & s_{n-1} = \text{'1'} \vee (s_{n-1} = \text{'2'} \wedge s_{n} \leq \text{'6'}) \\
0, & s_{n-1} = \text{'0'} \\
f_{n}, & \text{otherwise} 
\end{cases}
$$
