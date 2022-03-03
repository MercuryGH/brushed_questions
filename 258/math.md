# 数根

给定非负整数$n$，记它的十进制表示为$\overline{a_{m-1}\dots a_0}$，则它的十进制**数根**$f(n)$的递归定义如下：

$$
f(n) = \begin{cases}
n ,& n \leq 9, \\
f(\sum_{i=0}^{m-1}a_i) ,& \text{otherwise}
\end{cases}.
$$

请找出一个计算$n$的数根的$O(1)$算法。

## 解答

将$n$转写成进制表示的形式，得

$$
n = \sum_{i=0}^{m-1} a_i \cdot 10^i,
$$

根据$f(n)$中的提示，我们抽取一项$\sum_{i=0}^{m-1}a_i$出来，得到

$$
n = \sum_{i=0}^{m-1}a_i + \sum_{i=0}^{m-1}a_i(10^i - 1).
$$

注意到$10^i - 1$一定是$9$的倍数，因此

$$
n \equiv \sum_{i=0}^{m-1}a_i \pmod 9
$$

因此

$$
n \equiv f(n) \pmod 9
$$

又因为$0 \leq f(n) \leq 9$，因此我们还需要将同余类区间右移一位：从原本的取值范围$[0,8]$移动到$\{9\}\cup[1,8]$，并且对$n=0$的情况特判。

故我们得到了一般公式

$$
f(n) = \begin{cases}
(n-1) \bmod 9  + 1,& n \geq 1, \\
0, & n = 0
\end{cases}
$$


## 常用数论结论

对任意$k$进制数$n$：

$$
n \equiv \sum_{i=0}^{m-1}a_i \pmod {k-1}
$$

这个结论早就考过了。
