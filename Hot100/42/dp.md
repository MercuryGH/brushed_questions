# 接雨水

## 做题策略

### 连通器原理

考虑预处理一个 `lMaxHeight[]`和 `rMaxHeight[]`数组。

我们按列遍历每个积水点$i (i \in [1, n])$，记该积水点高 `height[i]`，其左端的最高墙高 `lMaxHeight[i]`，右端的最高墙高 `rMaxHeight[i]`，根据连通器原理，该积水点恰好存储了

$$
\min(\texttt{lMaxHeight[i]}, \texttt{rMaxHeight[i]}) - \texttt{height[i]}
$$

这么多水。需要注意的是，该值不能为负，因此还需要与$0$取 `max()`。

### 获取预处理的数组

第$i$个积水点左端的最高点的高度，可以是第$i - 1$个积水点左端的最高点的高度，或者是第$i - 1$个积水点的高度。即

$$
\texttt{lMaxHeight[i]} = \max(\texttt{lMaxHeight[i - 1]}, \texttt{height[i - 1]})
$$

获取右端最高点的高度的状态转移方程，也是类似的。
