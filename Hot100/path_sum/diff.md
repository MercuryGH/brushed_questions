# 相邻字符不同的最长路径

给定一颗树，每个结点都有一个字符权值$s_i$。

请找出树中的一条路径，其中任意一对相邻结点$(i, i+1)$均满足

$$
s_i \neq s_{i+1}.
$$

输出满足以上条件的路径的长度的最大值。

## 树形DP

如果没有$s_i \neq s_{i+1}$这个条件，那么本题就是在求树的直径。

### 二叉树的直径

记$f_{\text{node}}$表示以node为最高结点的向下路径的长度最大值，则

$$
f_{\text{node}} = \max(f_{\text{node.left}}, f_{\text{node.right}}) + 1.
$$

终结条件为$f_{\text{null}} = 0$。

答案应该保持更新为$f_{\text{node.left}} + f_{\text{node.right}} + 1$。

### 树的直径

记$f_{\text{node}}$表示以node为最高结点的向下路径的长度最大值，则

$$
f_{\text{node}} = \max_{\text{child} \in \text{children}(\text{node})}(f_{\text{child}}) + 1.
$$

终结条件为$f_{\text{null}} = 0$。

此处的答案更新需要注意：应该取每个node的两个最长的，以child结点为最高结点的向下路径。即集合$\{f_{\text{child}}\}, \text{child} \in \text{children}(\text{node})$中的两个最大值$u,v$（若集合中的元素不足两个，则用$0$补齐）。答案更新为$u + v + 1$。

### 本题

只是把纳入集合的条件增加一个$s_{\text{child}} \neq s_{\text{node}}$罢了。

但要注意，由于子结点的内容可能很丰富，因此尽管可能有$s_{\text{child}} = s_{\text{node}}$，但也不能放弃往child所在的子树继续DP。

时间复杂度为$O(n)$。
