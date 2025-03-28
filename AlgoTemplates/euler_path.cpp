#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#define MAXN 1050

using namespace std;

int G[MAXN][MAXN]; // 邻接矩阵
int du[MAXN]; // 节点的度数
stack<int> s; // 用于输出答案

int n, m; // V, E

void dfs(int u)
{
    for (int i = 1; i <= n; i++)
    {
        if (G[u][i])
        {
            G[u][i]--; // 过河拆桥！！
            G[i][u]--; // 过河拆桥！！
            dfs(i);
        }
    }
    s.push(u); // 回溯压栈的技巧，必须掌握！！
}

int main(void)
{

#ifdef DEBUG
    freopen("testdata.in","r",stdin);
#endif

    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        n = max(n, max(u,v)); // n 是顶点数
        G[u][v]++;
        G[v][u]++;
        du[u]++;
        du[v]++;
    }
    int start = 1;
    for (int i = 1; i <= n; i++)
    {
        if (du[i] % 2 == 1) // 欧拉通路的起点与终点必为奇数度节点
        {
            start = i; // 找到起点啦
            break;
        }
    }
    // 附：如果找不到奇数度节点，说明所有的欧拉通路都是欧拉回路，故直接start = 1处理即可。

    dfs(start);

    while(!s.empty()) // 输出答案
    {
        cout << s.top() << "\n";
        s.pop();
    }
    return 0;
}