# 二分答案后还有数学解

给定非负整数序列$a_n$，对于初始值$e$，序列$e_n$的生成方式如下：

$$
e_0 = e, \\
e_i = 2 e_{i-1} - a_i.
$$

请给出最小的$e$，使得序列$e_n$中不存在负数项。

## 解答

### 二分答案

正确性是显然的。时间复杂度$O(n \log n)$。

```cpp
bool check(const int initEnergy, const vector<int> &heights, const int maxHeight)
{
    int energy = initEnergy;
    for (int i = 0; i < n; i++)
    {
        energy += (energy - heights[i]); // e = 2 * e - h_i 会指数级增长！小心溢出！
        if (energy >= maxHeight)
        {
            return true;
        }
        if (energy < 0)
        {
            return false;
        }
    }
    return true;
}
int getMinimumInitialEnergy(const vector<int> &heights)
{
    const int maxHeight = *std::max_element(heights.begin(), heights.end());
    int l = 0;
    int r = maxHeight;

    int ans = -1;
    while (true)
    {
        if (l > r)
        {
            break;
        }

        const int mid = (l + r) / 2;
  
        if (check(mid, heights, maxHeight))
        {
            r = mid - 1;
            ans = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    if (ans == -1)
    {
        std::cout << "???" << "\n"; // 出了什么问题，实际上不可能走这一分支
    }
    return ans;
}
```

细节：在计算$e_i$时，由递推公式可知，$e_i$可呈指数级增长，坑题会爆 `long long`，因此需要提前用$\max(a_i)$剪枝。

### 数学方法

展开递推公式得

$$
\begin{aligned}
e_i &= 2e_{i-1} - a_i \\
    &= 2(2e_{i-2} - a_{i-1}) - a_i \\
    &= 2(2(2e_{i-3} - a_{i-2}) - a_{i-1}) - a_i \\
    &= \dots \\
    &= 2^{k+1} e_0 - (a_i + 2a_{i-1} + \dots + 2^k a_{1})
\end{aligned}
$$

其中$i - k = 1$，即$k = i - 1$。

故

$$
e_i = 2^{i} e_0 - \sum_{j=1}^{i} 2^{i-j}a_j.
$$

由题目要求知，$\forall i, e_i \geq 0 $。移项后化简得

$$
\begin{aligned}
e_0 &= \frac{e_i + \sum_{j=1}^{i} 2^{i-j}a_j}{2^{i}} \\
& \geq\frac{\sum_{j=1}^{i} 2^{i-j}a_j}{2^{i}} \\
&= \frac{2^{i}\sum_{j=1}^{i} 2^{-j}a_j}{2^{i}} \\
&= \sum_{j=1}^{i} \frac{a_j}{2^{j}} \\
\end{aligned}
$$

因此，若要使所有的$e_i \geq 0$，$e_0$的最小值就是$\max_{1 \leq i \leq n}(\lceil \sum_{j=1}^{i} \frac{a_j}{2^{j}} \rceil) = \lceil \sum_{j=1}^{n} \frac{a_j}{2^{j}} \rceil$。

直接$O(n)$求解即可，由于进行的都是除以2的幂的除法运算，所以答案通常都在 `double`精度范围内。

```cpp
int getMinimumInitialEnergy(const vector<int> &heights)
{
    double ans = 0;
    double twoPow = 2;
    for (int i = 0; i < n; i++)
    {
        ans += ((double)heights[i] / twoPow);
        twoPow *= 2;
    }

    return (int)std::ceil(ans);
}
```

### 数学倒推法

我们也可以用之前推出的公式进行倒推处理，从而得到一个不依赖小数计算的$O(n)$方法。

核心思想是证明一个引理：

**引理**

若$e$使得$e_n = 0$，则$e$是使得序列$e_n$中不存在负数项的最小的$e$。

**证明**

若$e$使得$e_n = 0$，则有

$$
e = \left \lceil \sum_{j=1}^n \frac{a_j}{2^j} \right \rceil
$$

若$e$不是使得序列$e_n$中不存在负数项的最小的$e$，则$e-1$也使得序列$e_n$中不存在负数项。但

$$
e - 1 \neq \left \lceil \sum_{j=1}^n \frac{a_j}{2^j} \right \rceil
$$

从而$e_n < 0$，矛盾。

于是，我们从$e_n=0$出发，通过公式

$$
e_{i-1} = \frac{e_i + a_i}{2}
$$

倒推出$e_0$即可。该方法不需要使用小数运算。
