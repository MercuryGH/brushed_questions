# 凸包

给定一个按顺序（未知是顺时针方向还是逆时针方向）连接的多边形的顶点，判断该多边形是否为凸多边形。

## 解答

不妨按照方向，依次设这些点为$\{P_1, \dots, P_n\}$，其中$(P_n, P_1)$尾首相连。

枚举每条边$(P_{i}, P_{i+1})$，考虑这条边的前驱$(P_{i-1}, P_i)$，计算二维向量叉乘（结果为一个标量）

$$
(P_{i}, P_{i+1}) \times (P_{i-1}, P_i)
$$

如果叉乘方向与前驱的叉乘$(P_{i-1}, P_i) \times (P_{i-2}, P_{i-1}) $方向一致，那么这两条边至少还是凸的（更确切地，可以通过结果的正负判断开口）。否则，我们发现了一个凹边，该多边形不是凸包。

该多边形是凸包，当且仅当根据以上规则，计算的所有叉乘的方向一致。

```cpp
bool isConvex(vector<vector<int>>& points) {
    const int n = points.size();
    long long pre = 0;
    long long cur = 0;

    for (int i = 0; i < n; i++) {
        const int x1 = points[i][0];
        const int x2 = points[(i + 1) % n][0];
        const int x3 = points[(i + 2) % n][0];
        const int y1 = points[i][1];
        const int y2 = points[(i + 1) % n][1];
        const int y3 = points[(i + 2) % n][1];

        const int dx1 = x2 - x1;
        const int dx2 = x3 - x2;
        const int dy1 = y2 - y1;
        const int dy2 = y3 - y2;

        cur = dx1 * dy2 - dx2 * dy1;
        if (cur != 0) { // 防止 n 点共线的情况发生
            if (cur * pre < 0) { // cur 和 pre 异号
                return false;
            }
            pre = cur;
        }
    }
    return true;
}
```
