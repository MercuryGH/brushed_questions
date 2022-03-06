# 正则表达式*.匹配

给定字符串$s$和正则表达式$p$，其中正则表达式的特殊字符只包含 `*`和 `.`。请判断$s$能否被$p$匹配。

## DP解

记$f_{i,j}$表示$s_{1:i}$能被$p_{1:j}$匹配。分类讨论：

* 若$p_j \neq \texttt{'*'}$，显然有
  $$
  f_{i,j} = \begin{cases}
  f_{i-1,j-1}, & s_i = p_j \vee p_j = \texttt{'.'} \\
  0, &\text{otherwise}
  \end{cases}
  $$
* 否则，我们考虑$p_{j-1}$是什么。显然$p_{j-1} \neq \texttt{'*'}$。如果$s_i = p_{j-1} \vee p_{j-1} = \texttt{'.'}$，那么相当于$s_i$完成了至少一个$p_{j-1}$的匹配，当前匹配成功当且仅当$f_{i-1,j} \vee f_{i, j-2}$；否则，我们只能期望这个 `*`匹配了0个字符，所以当前匹配成功当且仅当$f_{i,j-2}$。

综上，状态转移方程如下：

$$
f_{i,j} = \begin{cases} p_j \neq \texttt{'*'} \begin{cases}
f_{i-1,j-1}, & s_i = p_j \vee p_j = \texttt{'.'} \\
0, &\text{otherwise}
\end{cases}\\
\text{otherwise}
\begin{cases}
f_{i-1,j} \vee f_{i, j-2}, & s_i = p_{j-1} \vee p_{j-1} = \texttt{'.'} \\
f_{i, j-2}, &\text{otherwise}
\end{cases}\\
\end{cases}
$$

这DP还是太鬼了。
