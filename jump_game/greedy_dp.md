# 跳跃游戏2

给定格子序列$a_n$，当玩家站在第$i$个格子上时，最大跳跃距离为$a_i$。

初始时，玩家站在第$1$个格子上，请给出跳到第$n$个格子所需的最小跳跃次数。若没有办法跳到第$n$个格子，也请输出$+\infin$。

## DP解

### 朴素

记$f_i$为跳到第$i$个格子所需的最小跳跃次数，则$f_n$为答案，$f_1 = 0$。

状态转移方程为

$$
f_i = \min_{j \in [1,i), j + a_j \geq i} (f_j) + 1.
$$

解这个DP的时间复杂度居然是$O(n^2)$的，看看有没有优化空间。

### 贪心优化

**引理**

序列$f_n$单调不减。

**证明**

显然的。

---

所以，DP方程可以简化为

$$
f_i = f_{j} + 1,
$$

其中$j = \min\{j \in [1, i) : j + a_j \geq i \}$。

于是，我们用一个线性扫描，每次贪心地更新当前格子能跳到的所有$f_i$即可，而且，**如果该格子已经被更早地更新过，那么我们便不再关心它**。这样一来，每个格子被写入$f_i$的次数恰好就是$1$次，因此时间复杂度为$O(n)$。

实现这个贪心策略，只需维护一个“当前能跳到的最远距离”变量即可。

```cpp
int jump(vector<int> &nums)
{
    const int n = nums.size();
    vector<int> dp(n, INF);
    dp[0] = 0;

    int maxReach = 0;
    for (int i = 0; i < n; i++)
    {
        const int curReach = std::min(n - 1, i + nums[i]);
        if (curReach > maxReach)
        {
            for (int j = maxReach + 1; j <= curReach; j++)
            {
                dp[j] = dp[i] + 1;
            }
            maxReach = curReach;
        }
    }
    return dp[n - 1];
}
```
