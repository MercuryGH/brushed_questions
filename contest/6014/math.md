# 统计可以被 K 整除的下标对数目

给定列表$a_n$和正整数$k$，请找出有多少个下标对$(i, j), 0 \leq i < j \leq n - 1$，满足$k | (a_i \cdot a_j)$。

**例**

$a_n = \{1, 2, 3, 4, 5\}, k = 2$，则只有这些如下$7$个结果是合法的。故答案为$7$。

$$
2 | (1 \times 2), \\
2 | (1 \times 4), \\
2 | (2 \times 3), \\
2 | (2 \times 4), \\
2 | (2 \times 5), \\
2 | (4 \times 3), \\
2 | (4 \times 5), \\
$$

## 解答

暴力$O(n^2)$过不了。

首先证明一个引理。

**引理**

记$k, a, b$为三个正整数，则$k | (ab)$当且仅当$k | \gcd(a, k) \cdot \gcd(b, k)$。

**暴力证明**

记$a,b,k$的直到第$t$个素数的素因数分解为

$$
a = p_1^{q_1} p_2^{q_2} \dots p_t^{q_t}, \\
b = p_1^{r_1} p_2^{r_2} \dots p_t^{r_t}, \\
k = p_1^{s_1} p_2^{s_2} \dots p_t^{s_t}, \\
$$

$\to$：我们有

$$
ab = \prod_{i=1}^t p_i^{q_i + r_i},
$$

故$k | (ab)$意味着$\forall i, s_i \leq q_i + r_i$。

而

$$
\gcd(a, k) = \prod_{i=1}^t p_i^{\min(q_i, s_i)}, \\
\gcd(b, k) = \prod_{i=1}^t p_i^{\min(r_i, s_i)}, \\
$$

故

$$
\gcd(a, k) \cdot \gcd(b, k) = \prod_{i=1}^t p_i^{\min(q_i, s_i) + \min(r_i, s_i)}
$$

要证明$k|(\gcd(a, k) \cdot \gcd(b, k))$，只需证$\forall i, s_i \leq \min(q_i, s_i) + \min(r_i, s_i)$。由条件$s_i \leq q_i + r_i$，这是易得的（严谨证明，需要枚举$q_i$和$s_i$的大小关系，$r_i$和$s_i$的大小关系，共$4$种情况分类讨论证明）。

$\leftarrow$：只需从$\forall i, s_i \leq \min(q_i, s_i) + \min(r_i, s_i)$证明到$\forall i, s_i \leq q_i + r_i$，原理和过程类似。

Q.E.D.


根据引理，我们可以考虑预处理一个哈希表，其key集为$\text{gcd}(a_i, k)$所有可能的结果，value为该结果出现的次数。可见该哈希表的key集的最大容量为$k$的因子数目，由于只有素数乘积才能决定某个数的因子数，因此这个key集的大小的数量级应该是很小的。

然后，我们在这个哈希表上做二重循环即可。对于某个查询的key $k_1$，我们只考虑后半key $k_2 \leq k_1$的情况来避免重复。对于

* $k_2 < k_1$的情况，我们计入$v_2v_1$组
* $k_2 = k_1$的情况，此时必有$v_1=v_2$，我们计入$\binom {v_1} 2$组。

整体时间复杂度$O(n \log k + \tau^2(k))$，空间复杂度$O(\tau(k))$，其中$\tau(k)$为$k$的因子数。
