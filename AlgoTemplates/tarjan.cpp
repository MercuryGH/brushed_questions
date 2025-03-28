#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#define MAXN 10010

using namespace std;

vector<int> G[MAXN]; // 邻接表正确使用方法
stack<int> s;

int n, m; // V, E

bool used[MAXN], vis[MAXN];
// 分别表示i是否被tarjan过；i是否在栈中
int dfn[MAXN], low[MAXN], color[MAXN], num[MAXN];
// 分别表示dfs到达i的次序号；i能够回溯到的最早位于栈中的节点；i属于第几个强连通分量；第i个强连通分量的节点数
int colornum = 0, cnt = 0, ans = 0;
// 分别表示强连通分量的总数；当前访问的次序号（时间戳）；点数大于1的强联通分量个数

void paint(int x)
{
    s.pop();
    // cout << x << " ";
    color[x] = colornum;
    num[colornum]++;
    vis[x] = 0;
}

void tarjan(int x)
{
    dfn[x] = low[x] = ++cnt;  // 在low更新前，low和dfs是一样的
    s.push(x);
    vis[x] = used[x] = 1;
    for (unsigned int i = 0; i < G[x].size(); i++)  // 访问结点x的每个邻接点
    {
        int q = G[x][i];  // q是x的邻接点
        if (!dfn[q])  // 或者写 if (!used[q])
        {
            tarjan(q);  // 递归
            low[x] = min(low[x], low[q]);  // 由于继续深度搜索，所以可能更新low的值
        }
        else if (vis[q])
        {
            low[x] = min(low[x], low[q]);  
            // 即使q已经被dfs过了，如果q在栈里面，仍有可能更新
            // 这一句也可以写成low[x] = min(low[x], dfn[q]); 两者都是正确的（但为什么呢？思考起来有点难度）
        }
    }
    if (low[x] == dfn[x])
    // 当一个节点的dfn值和low值相等时，这个节点是一个强联通分量的“根”。压栈，输出。
    {
        colornum++;
        while (s.top() != x)
            paint(s.top());
        paint(x);
        // cout << "\n";
    }
}

int main(void)
{

#ifdef DEBUG
    freopen("testdata.in", "r", stdin);
#endif

    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
    }
    for (int i = 1; i <= n; i++)
    {
        if (!used[i])
            tarjan(i);
    }

    for (int i = 1; i <= colornum; i++)
    {
        if (num[i] > 1)
            ans++;
    }
    cout << ans << "\n";
    return 0;
}