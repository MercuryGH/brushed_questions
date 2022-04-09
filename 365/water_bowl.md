# 水壶问题

有两个水壶，最大容量分别为$n, m$。水的供应无限，水壶没有刻度。初始时，水壶为空。给定正整数$k$，请问

1. 是否有可能使用这两个水壶经过若干次装水、倒水，得到准确的体积为$k$的水？这些水可以通过从其中一个水壶，或者两个水壶装的水之和得到。
2. 若可能，请给出一个操作次数最少的方案。你的每一次操作可以列出如下：
   * 装满任意一个水壶；
   * 清空任意一个水壶；
   * 从其中一个水壶向另外一个水壶倒水，直到装满或者倒空。

## 解答

### 状态机思维

考虑当两个水壶装有体积为$a, b$时的状态为$(a,b)$。不妨设$n \leq m$，列出若干状态转移途径：

* $(0,0) \to (n, 0)$；装满第一个水壶
* $(0, 0) \to (0, m)$；装满第二个水壶
* $(0, m) \to (n, m - n)$；让第二个水壶倒满第一个水壶
* $(n, m - n) \to (0, m - n)$；倒空第一个水壶
* ……

那么，问题转换为，在状态转移图中，从$(0,0)$是否存在一条合法路径，到达$(?, k)$或$(k, ?)$或$(k - t, t)$。

在进行状态转移时，有$6$种选择，注意剪枝：

```cpp
vector<State> getNextStates(const State curState, const int jug1Capacity, const int jug2Capacity) {
    vector<State> nextStates;
    if (curState.a < jug1Capacity)
        nextStates.emplace_back(jug1Capacity, curState.b); // 装满第一个
    if (curState.b < jug2Capacity)
        nextStates.emplace_back(curState.a, jug2Capacity); // 装满第二个

    if (curState.a > 0)
        nextStates.emplace_back(0, curState.b); // 清空第一个
    if (curState.b > 0)
        nextStates.emplace_back(curState.a, 0);

    const int bCanHold = jug2Capacity - curState.b;
    // 从 A 尽可能倒水到 B
    const int waterExchangeA2B = std::min(bCanHold, curState.a);
    if (waterExchangeA2B > 0) 
        nextStates.emplace_back(curState.a - waterExchangeA2B, curState.b + waterExchangeA2B);

    const int aCanHold = jug1Capacity - curState.a;
    // 从 B 尽可能倒水到 A
    const int waterExchangeB2A = std::min(aCanHold, curState.b);
    if (waterExchangeB2A > 0) 
        nextStates.emplace_back(curState.a + waterExchangeB2A, curState.b - waterExchangeB2A);

    return nextStates;
}
```

若要输出方案，只需用一个哈希表记录每个结点的前驱，然后最后用栈倒序输出即可。

时间复杂度为$O(nm)$。

### 找gcd

首先证明一个引理。

**引理**

每次进行状态转移时，我们只需考虑让水的总量增加或减少$n$或$m$的操作方案。

**证明**

* 首先要清楚，在题目所给的操作下，两个桶不可能同时有水且不满。因为观察所有题目中的操作，操作的结果都至少有一个桶是空的或者满的；

* 其次，对一个不满的桶加水是没有意义的。因为如果另一个桶是空的，那么这个操作的结果等价于直接从初始状态给这个桶加满水；而如果另一个桶是满的，那么这个操作的结果等价于从初始状态分别给两个桶加满；

* 再次，把一个不满的桶里面的水倒掉是没有意义的。因为如果另一个桶是空的，那么这个操作的结果等价于回到初始状态；而如果另一个桶是满的，那么这个操作的结果等价于从初始状态直接给另一个桶倒满。

证毕。

那么，问题转换成，是否存在整数$a,b$，满足

$$
an + bm = k
$$

其中$a,b$代表某种操作的个数，这种操作将水的总量变化了$ an, am$。初始状态下，$a=b=0$。

由贝祖定理，上式有整数解，当且仅当$k | \gcd(n,m)$。注意特判

* $n ,m$中存在$0$的情况。
* $k > n + m$的情况。

时间复杂度为$O(\log(\min(n, m)))$。
