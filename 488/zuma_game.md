# 高级搜索——祖玛

给定一个字符序列$c_n$，其中包含若干种字符。再给定一个玩家所拥有的“字符：个数”键值对。现在，玩家希望通过发射最少的字符，达到将$c_n$清零的效果（$c_n$中任意位置连续$n (n \geq 3)$个相同字符会被自动消除），求发射数目的最小值。

## BFS

最小化“发射字符数目”，BFS比DFS更合适。