# 阶乘后的零

请给出$n!$的十进制表示的后导零的数目。

## 解答

后导零的数目与$n!$能被$10$整除的次数相同。注意到$10$只能被分解成$2 \times 5$，所以我们只需要找到$n!$的$2, 5$的因子数即可。

先找规律：

$$
\begin{aligned}
11 ! &= 11 \times 10 \times \dots \times 1 \\
&= 11 \times (2 \times 5) \times 9 \times (4 \times 2) \times 7 \times (3 \times 2) \times (5) \times (2 \times 2) \times 3 \times (2) \times 1
\end{aligned}
$$

注意到含有$2$的因子项每隔一个自然数出现一次，含有$5$的因子项每隔$5$个出现一次，于是我们知道，每找到一个$5$，就一定能找到一个$2$与之配对。因此我们只需要找到$n!$的被$5$整除的次数即可。

基于以上思路，容易给出暴力的$O(n\log n)$解：

```cpp
int trailingZeroes(int n) {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        int curNum = i;
        while (curNum > 0) {
            if (curNum % 5 == 0) {
                cnt++;
                curNum /= 5;
            } else {
                break;
            }
        }
    }
    return count;
}
```

但是这样显然不够数学。我们发现，我们只对$5$的倍数感兴趣，对于一个能够被$5^k$整除的$n$，它至少可以为$n!$贡献$\frac{n!}{5^k}$个因子$5$。不难推出，定义$f(n)$为$n!$的进制表示的后导零的数目，我们有

$$
f(n) = \sum_{k=1}^{\infty} \left \lfloor \frac{n}{5^k} \right \rfloor
$$

所以我们只需要枚举$5$的幂即可。实际计算中，$k$大于某个数后，$\left \lfloor \frac{n}{5^k} \right \rfloor = 0$就恒成立了。

```cpp
int trailingZeroes(int n) {
    int ans = 0;
    for (int cur = 5; ; cur *= 5) {
        if (n / cur == 0) {
            break;
        }
        ans += (n / cur);
    }
    return ans;
}
```

时间复杂度优化为$O(\log n)$。

# 进阶

对于任意非负整数$k$，请实现函数$g(k)$，其输出使得$f(n) = k$的$n$的数目。

## 解答

**引理**

$g(k) = 0$，或$g(k) = 5$。

**证明**

我们将会用到如下的不等式：

**不等式引理**

$$
\lfloor a + b\rfloor \geq \lfloor a\rfloor + \lfloor b \rfloor
$$

当且仅当$\text{frag}(a) + \text{frag}(b) < 1$时取等。其中$\text{frag}(a)$表示$a$的小数部分。

证明留作练习。

* 首先证明$g(k) \leq 5$。对任意$n$，其5个后继为$n + 1, \dots, n+4, n+5$。注意到

$$
f(n) = \sum_{k=1}^{\infty} \left \lfloor \frac{n}{5^k} \right \rfloor,\\
f(n + 5) = \sum_{k=1}^{\infty} \left \lfloor \frac{n + 5}{5^k} \right \rfloor \geq f(n) + \sum_{k=1}^{\infty} \left \lfloor \frac{5}{5^k} \right\rfloor = f(n) + 1 > f(n),
$$

故对任意长度至少为$6$的正整数闭区间$[n, n + 5]$，其中元素的$f()$值不相等。又由于$f(n)$显然单调不减，于是$g(k) > 6$不成立，证毕。

* 然后证明$g(k) \notin \{1,2,3,4\}$。任取$n = 5i (i \geq 0) $，仍然考虑其$4$个后继$n + 1, \dots, n+ 4$，这$4$个后继都不是$5i$的形式。考虑

$$
f(n + 4) = \sum_{k=1}^{\infty} \left \lfloor \frac{5i + 4}{5^k} \right \rfloor = \sum_{k=1}^{\infty} \left \lfloor \frac{5i}{5^k} + \frac{4}{5^k} \right \rfloor
$$

我们取最小的$k' \in \{1,2,\dots\}$，使得$\left \lfloor \frac{5i}{5^{k'}} \right \rfloor = 0$，那么由取等条件得

$$
\begin{aligned}
f(n + 4) &= \sum_{k=1}^{k' - 1} \left \lfloor \frac{5i}{5^k} + \frac{4}{5^k} \right \rfloor + \left \lfloor \frac{5i}{5^{k'}} + \frac{4}{5^{k'}} \right \rfloor \\
&= \sum_{k=1}^{k' - 1} \left \lfloor \frac{5i}{5^k} \right \rfloor +\sum_{k=1}^{k' - 1} \left \lfloor \frac{4}{5^k} \right \rfloor +\left \lfloor \frac{5i}{5^{k'}} \right \rfloor + \left \lfloor \frac{4}{5^{k'}} \right \rfloor \\
&= \sum_{k=1}^{k' - 1} \left \lfloor \frac{5i}{5^k} \right \rfloor \\
&= f(n)
\end{aligned}
$$

于是对任意以$5$的倍数为起始的，长度为$5$的正整数闭区间$[n, n + 4]$，该区间内的元素的$f()$值均相等。故不存在$g(k)$可取$\{1,2,3,4\}$。

* 接下来我们证明$g(k)$可以取$0$或者$5$。显然对于$k = 0$，有且只有$n \in \{0, 1, \dots ,4\} $满足$f(n) = 0$，故$g(0) = 5$。又因为$f(24) = 4, f(25) = 6$，由$f$的不减性知$g(5) = 0$。

证毕。

我们观察到，$f(24),f(25)$出现跳变的原因是$25$是$5$的幂次，因此提供了额外的因子$5$。显然$f(125)$等也存在这样的跳变。

接下来，不同类型的程序员会有不同的思路：

### 数学思路

那么，如何判断$g(k)$究竟是$0$还是$5$呢？我们只要判断是否存在$n$，使得$f(n)=k$即可，如果存在这样的$n$，$g(k) = 5$，反之$g(k) = 0$。设每一个合法的$n$的$5$进制表示为

$$
n = 5^{m-1}a_{m-1} + \dots + 5^0a_{0}
$$

其中$a_j \in [0, 5)$。可以算出

$$
\begin{aligned}
f(n) &= \sum_{k=1}^{\infty} \left \lfloor \frac{\sum_{j=0}^{m-1}5^ja_j}{5^k} \right \rfloor \\
&= \left \lfloor \frac{\sum_{j=1}^{m-1}5^ja_j}{5} \right \rfloor + \left \lfloor \frac{\sum_{j=2}^{m-1}5^ja_j}{5^2} \right \rfloor + \dots + \left \lfloor \frac{\sum_{j=m-1}^{m-1}5^ja_j}{5^{m-1}} \right \rfloor \\
&= 5^0a_1 + (5^0 + 5^1)a_2 + \dots + (5^0 + \dots + 5^{m-1}) a_{m-1}
\end{aligned}
$$

由于$f(5^m) = 5^{m - 1} + \dots + 5^{0}$，故上式可以改写成

$$
f(n) = \sum_{i=0}^{m-1} a_if(5^{i+1}).
$$

由等比数列求和公式

$$
f(n) = \sum_{i=0}^{m-1} \frac{a_i (5^i - 1)}{4}.
$$

于是，只需要判断给出的$k$是否能写成以上的形式即可。

那么，如何判断$k$是否能写成以上的形式呢，需要枚举$a_i$的值吗？

确实可以考虑枚举$a_i$的值做搜索……但这样效率稍低。我们考虑判断$k$是否能写成由序列$\{\frac{5^i-1}{4}\}$确定的，每系数都小于$5$的**变进制数**。为了方便计算，我们先求出序列$\{\frac{5^i-1}{4}\}$的递推公式：

$$
c_i = 5{c_{i-1} + 1}, c_0 = 0
$$

然后，我们确定数的表示范围的上界，即找到最小的$c_i$，满足$c_i \geq k$。此时，$k$至少可以被变进制数$1\dots1$（$i$个1）表示。那么，只要对其进行进制转换，找出实际的进制系数，若发现其不在之前规定的范围$[0,5)$内，则认为$k$不可被这种形式表示；否则，$k$可以被表示，输出$5$。

时间复杂度为$O(\log k)$。

```cpp
int preimageSizeFZF(int k) {
    int acc = 0;
    while (acc < k) {
        acc *= 5;
        acc += 1;
    }

    int cur = k;
    while (cur > 0) {
        acc -= 1;
        acc /= 5;
        if (cur / acc >= 5) {
            return 0;
        }
        cur %= acc;
    }
    return 5;
}
```

### 二分答案思路

由于$f()$是单调不减的，故我们可以考虑用二分答案的方式找满足$f(n) = k$的$n$的最小值和最大值。若找得到$n$的最小值和最大值相差为$5$，则输出$5$，否则输出$0$。

或者根据已知条件更直接地，直接对某个区间二分查找$n$，询问是否存在$f(n) = k$即可。若找得到，则输出$5$，否则输出$0$。

接下来计算二分区间的上下界。考虑

$$
\begin{aligned}
f(n) &= \sum_{k=1}^{\infty} \left \lfloor \frac{n}{5^k} \right \rfloor, \\
& \leq \sum_{k=1}^{\infty} \frac{n}{5^k} \\
&= \frac{n}{4} 
\end{aligned}
$$

由于给定的是$k$，且$f(n)=k$，那么有$k \leq \frac{n}{4}$，$n \geq 4k$。

另一方面，如下**构造**一个$n$的下界

$$
\begin{aligned}
f(5n) &= \sum_{k=1}^{\infty} \left \lfloor \frac{5n}{5^k} \right \rfloor, \\
& = \frac{5n}{5} + \sum_{k=2}^{\infty} \left \lfloor \frac{5n}{5^k} \right \rfloor \\
& \geq n 
\end{aligned}
$$

因此$n \leq f(5n)$，即$\frac{n}{5} \leq k$，$n \leq 5k$。

综上，只需在区间$[4k,5k]$中二分$n$即可。时间复杂度为$O(\log k \log k)$。

```cpp
class Solution
{
    long long trailingZeroes(long long n)
    {
        long long ans = 0;
        for (long long cur = 5;; cur *= 5)
        {
            if (n / cur == 0)
            {
                break;
            }
            ans += (n / cur);
        }
        return ans;
    }

public:
    int preimageSizeFZF(int k)
    {
        long long l = 4ll * k;
        long long r = 5ll * k;
        while (true) {
            if (l > r) {
                return 0;
            }

            const long long mid = (r - l) / 2 + l;
            const long long zeroNum = trailingZeroes(mid);
            if (zeroNum == k) {
                return 5;
            } else if (zeroNum < k) {
                l = mid + 1;
            } else { // zeroNum > k
                r = mid - 1;
            }
        }
        return 0;
    }
};
```
