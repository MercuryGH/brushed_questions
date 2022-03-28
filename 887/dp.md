# 大楼摔鸡蛋问题

给定一个有$n$层的大楼（$n \geq 1$），已知在其中某一层$f \ (f \in [0,n])$及其以下的所有楼层，鸡蛋从窗户扔下来都不会摔碎；在该层以上的所有楼层，鸡蛋从窗户扔下来都会摔碎。我们称第$f$层为“临界楼层”。

例如，有可能在第$1$层就会摔碎，此时第$0$层就是“临界楼层”。也有可能在第$n$层也不会摔碎，此时第$n$层就是“临界楼层”。

现在，给定$k$个鸡蛋，你每次都可以在$[1,n]$中选择一个楼层编号扔鸡蛋，然后记录它的破碎情况。请你给出一种策略，保证找出那个“临界楼层”$f$，并使得你扔鸡蛋的次数最小化。请注意：如果鸡蛋摔碎了，那么就不能再次利用了；否则可以再次利用。

PS：当$k = 1$或$k \geq \lceil \log_2 n \rceil$时，有显然的解法。

## DP解

我们注意到无论是否摔碎鸡蛋，都会导致问题$(n,k)$转变为子问题（要么在更高的楼层找，要么在更低的楼层找），因此考虑动态规划。

### 朴素DP

记$f_{i,j}$表示在长度为$i$的楼层区间，用$j$个鸡蛋保证找出临界楼层，扔鸡蛋的最小次数。则答案在$f_{n, k}$。

由于我们可以选择在楼层区间的第$k  \ (k \in [1,i])$个元素上扔鸡蛋，所以：

* 若鸡蛋在该层摔碎，我们只剩$j-1$个鸡蛋，然后向下找$k-1$个楼层；
* 若鸡蛋在该层没有摔碎，我们仍手持$j$个鸡蛋，然后向上找$i - k$个楼层。

无论是否摔碎，我们都消耗了一次扔鸡蛋的次数。为了保证找出临界楼层，我们需要取以上两种情况子问题的答案的最大值，然后枚举$k$取最小值。

故最终结果为一个minimax形式：

$$
f_{i,j} = \min_{k \in [1, i]}(\max(f_{k-1, j-1}, f_{i-k, j})) + 1.
$$

初值条件：

* $f_{0, j} = 0$。直接确定临界楼层就是地板。
* 当$i \geq 1$时，$f_{i, 0} = +\infty$。没有鸡蛋，无论如何都无法完成计算。
* 当$j \geq 1$时，$f_{1, j} = 1$。恰好扔一次一定能够确定。
* $f_{i, 1} = i$。平凡情况，最坏情况下必须从低层到高层一个一个试才能确定。

```cpp
int superEggDrop(int k, int n)
{
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
    for (int j = 0; j <= k; j++) {
        dp[0][j] = 0;
        dp[1][j] = 1;
    }
    for (int i = 1; i <= n; i++) {
        dp[i][0] = INF;
        dp[i][1] = i;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            int res = INF;
            for (int l = 1; l <= i; l++) {
                res = std::min(res, std::max(dp[l - 1][j - 1], dp[i - l][j]));
            }
            dp[i][j] = res + 1;
        }
    }
    return dp[n][k];
}
```

时间复杂度为$O(n^2k)$。

### 优化DP过程

> 可视化建议看LeetCode题解

注意到minimax总是可以用二分答案优化。我们需要找到的是这样的一个$k \in [1,i]$，使得$\max(f_{k-1, j-1}, f_{i-k,j})$最小。注意到$f_{k-1,j-1}$相对于$k$是单调不减的，$f_{i-k, j}$相对于$k$是单调不增的，更进一步地，我们可以证明它们都是离散连续的（所有在区间内的离散的点一定能被取到，即不存在$i, |f_{i,j} - f_{i+1,j}| \geq 2$）。

注意：$\max()$两者的值不一定有机会在$f_{k-1,j-1} = f_{i-k,j}$时取到，这是因为完全可能存在其中一项完全处于另一项的上方的可能性，即$f_{k-1,j-1} > f_{i-k,j}$恒成立，反过来也一样。但是，如果我们有机会找到$f_{k-1,j-1} = f_{i-k,j}$，那么答案一定就是其中之一，直接输出结果即可。

因此，我们只需找到一个接近于山谷的$k$，那么$\max$两者的值一定也是最小的。

```cpp
int binarySearchK(const vector<vector<int>> &dp, const int i, const int j) {
    int ans = INF;
    int l = 1;
    int r = i;
    while (true) {
        if (l > r) {
            break;
        }
        const int mid = (l + r) / 2;
        const int broken = dp[mid - 1][j - 1]; // 随 mid 单调不减
        const int notBroken = dp[i - mid][j]; // 随 mid 单调不增

        if (notBroken == broken) { // 提前找到，退出
            ans = broken;
            break;
        }

        if (notBroken > broken) { // 在左边
            ans = std::min(ans, notBroken);
            l = mid + 1;
        } else { // 在右边
            ans = std::min(ans, broken);
            r = mid - 1;
        }
    }
    return ans;
}

int superEggDrop(int k, int n)
{
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
    for (int j = 0; j <= k; j++) {
        dp[0][j] = 0;
        dp[1][j] = 1;
    }
    for (int i = 1; i <= n; i++) {
        dp[i][0] = INF;
        dp[i][1] = i;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            dp[i][j] = binarySearchK(dp, i, j) + 1;
        }
    }
    return dp[n][k];
}
```

时间复杂度优化为$O(nk \log n)$。
