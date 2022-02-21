## 判断两区间是否重叠

```cpp
bool isOverlapWith(const Interval &interval) {
    return max(this->l, interval.l) <= min(this->r, interval.r)
}
```

注意区间的开闭可能影响到取整条件。

## 全排列子串

给定字符串 `s1`和句子 `s2`，判断 `s1`的某个排列是否是 `s2`的子串。

暴力做法：记$n$为 `s1`的长度，`sort(s1)`为 `s1`排序的结果。在 `s2`遍历所有长度为$n$的滑动窗口，比较窗口内部排序的结果是否为 `sort(s1)`，若是，则输出 `true`；若所有窗口均不是，则输出 `false`。
