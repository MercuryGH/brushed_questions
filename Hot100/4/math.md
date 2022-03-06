# 找出两个有序数组合并后的中位数

给定两个有序序列（用数组存储）$a_n, b_m$，请找出其中所有元素的中位数。

## 暴力解

合并两个有序数组$O(n+m)$，找出中位数$O(1)$。总体需要$O(n+m)$时间复杂度。

## 奇妙二分

先证明中位数的一个性质。

**引理**

有序序列$a_n = \{a_1,a_2, \dots, a_n\}$的中位数的值为

$$
\frac{a_{\lfloor\frac{n+1}{2}\rfloor} + a_{\lfloor\frac{n+2}{2}\rfloor}}{2}.
$$

**证明**

分奇偶讨论即可。留作练习。

--- 

那么，我们的目的就是找出$a_n, b_m$合并后的数组$c_{n+m}$的第$\lfloor \frac{n+m+1}{2} \rfloor$个元素和第$\lfloor \frac{n+m+2}{2} \rfloor$个元素了。我们考虑在两个数组上二分。定义一个函数，找出$c_{n+m}$的第$k$大元素，其算法如下：

1. 取$a_n$的第$\lfloor \frac{k}{2} \rfloor$大元素，$b_m$的第$\lfloor \frac{k}{2} \rfloor$大元素比较。
2. 如果前者小于后者，则说明$a_n$的第$1 \leq i \leq \lfloor \frac{k}{2} \rfloor$大元素都无法成为$c_{n+m}$的第$k$个元素。此时我们只取$a_{k - \lfloor \frac{k}{2} \rfloor:n}$和$b_m$，然后递归下去找$c_{n+m}$的$k - \lfloor \frac{k}{2} \rfloor$大元素即可。
3. 如果后者小于或等于前者，我们只取$a_{n}$和$b_{k - \lfloor \frac{k}{2} \rfloor:m}$，然后递归下去找$c_{n+m}$的$k - \lfloor \frac{k}{2} \rfloor$大元素即可。

注意边界条件：如果$k = 1$，只需取$\min(a_1,b_1)$；如果其中一个数组（如$a$）被递归成了空数组，只需返回$b_{k}$即可。

算法的整体时间复杂度确实是$O(\log (n+m))$的。
