# 将正偶整数$n$分解成若干正偶整数之和，每个正偶整数只能用一次

返回使用的正偶整数最多的方案之一。

**例1**

$n=12$，一个拆分方案为$\{2, 4, 6\}$。

**例2**

$n=28$，一个拆分方案为$\{2, 4, 6, 16\}$，另一个拆分方案为$\{2, 6, 8, 12\}$。

## 贪心策略描述

首先，对于$n$为奇数的情况，必然不能拆分。

对于$n$为偶数的情况，用$a_i \in \{2, 4, \dots, 2n\}$来遍历，能拆就拆。如果剩余的

$$
remain = n - \sum_{i=1}^k a_i
$$

不够用$a_{k+1}$来拆，即我们找出了最小的$k$，使得$\sum_{i=1}^k a_i \leq n < \sum_{i=1}^{k+1} a_i$。这时，我们的策略认为，若

* 前一个式子能取等，则直接返回拆分方案$\{a_1, \dots,a_k\}$即可。
* 前一个式子不能取等，则直接返回拆分方案$\{a_1,\dots,a_{k-1}, n - \sum_{i=1}^{k-1} a_i\}$即可。

```cpp
vector<long long> maximumEvenSplit(long long finalSum) {
    if (finalSum % 2 == 1) {
        return {};
    }

    vector<long long> ans;
    long long sum = 0;
    for (long long i = 2; ; i += 2) {
        long long prevSum = sum + i;
        if (prevSum + i + 2 > finalSum) {
            if (sum == finalSum) {
                ans.push_back(i);
            } else {
                ans.push_back(finalSum - sum);
            }
            break;
        }
        ans.push_back(i);
        sum = prevSum;
    }
    return ans;
}

```

### 贪心策略证明

记$S_n$为对$n$的某个最优拆分方案，我们证明该贪心策略与$S_n$的相容性。

将$S_n$按照从小到大排序，分别记为$\{S_1, S_2, \dots\}$，并记$E =\{2, 4, \dots, 2n\}$，显然$S_n$中任一元素必须属于$E$。记$a_1 = 2$为贪心策略选出的第一个$E$，若

* $a_1=S_1$，相容。
* $a_1 < S_1$，由于大于$4$的任一正偶数$S_1$均可以表示成至少两个不同的正偶数之和，且贪心策略在后面仍然可以选择$S_1$，故选择$a_1$不会比选择$S_1$差。相容。

问题规模被缩小。证毕。
