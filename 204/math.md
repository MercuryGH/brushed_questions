# 素数筛

给定正整数$n$，给出$[2,n]$中素数的数目。

暴力计数$O(n \sqrt n)$，但我们有更好的算法。

## 埃氏筛

空间换时间的味道。

对每一个$i \in [2, n]$，我们在判断它是否为素数之前，查一个 `isPrime[i]`的表，若表里面已经为 `false`，则不必再对它做循环，直接取下一个$i$即可。

`isPrime[]`会在每个$i$在循环判断素数后更新——若$i$确实是素数，则$2i, 3i, \dots, ki$一定是合数（$ki \leq n$），那么只要设这些数的 `isPrime[]`值为 `false`，就能在后续遍历到该数时节省判断时间。

`isPrime[]`表初始化为全 `true`。

```cpp
int countPrimes(int n) {
    vector<bool> isPrime(n, true);

    int ans = 0;
    for (int i = 2; i < n; i++) {
        if (isPrime[i] == true) {
            ans++;
            for (int j = 2; i * j < n; j++) {
                isPrime[i * j] = false;
            }
        }
    }
    return ans;
}
```

该算法的时间复杂度上界分析如下：

我们考虑对每个$i$，都要枚举$2i, 3i, \dots, ki$，其中$k$是满足$ki \leq n$的最大$k$。那么，对每个$i$，枚举的次数

$$
k \approx \frac{n}{i},
$$

在$[2,n]$中枚举次数之和的上界为

$$
\sum_{i=2}^n \frac{n}{i} = n \sum_{i=2}^n \frac{1}{i} = O(n \log n).
$$

故时间复杂度$O(n \log n)$优于暴力筛。

事实上，由于只对素数进行枚举，所以埃氏筛的确切时间复杂度为

$$
\sum_{p\text{是素数}, p \leq n}\frac{n}{p} = O(n \log \log n).
$$

证明详见 [(75 封私信 / 80 条消息) 为什么埃式筛法的时间复杂度是O(nloglogn)？ - 知乎 (zhihu.com)](https://www.zhihu.com/question/35112789?sort=created)

## 线性筛（欧拉筛）

难以理解，不学了。

## 不是极限

还有更优（例如$O(n^{0.75})$）的算法，更加复杂。
