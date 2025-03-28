#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;

int n, m;
int head[5010], dis[5010], addcnt, cnt, ans;
//head[i] is the **pos of the 1st edge** that starts with **i node**
bool visited[5010];
struct edge
{
    int next, to, dis;
    //e[i].next is the succeed of edge that has the same starting point with i edge
} e[400010];
struct node
{
    int dis, pos;
    bool operator < (const node &x) const//Get the less one according to the < rule
    {
        return x.dis < dis;
    }
};
priority_queue<node> hp;

void _init()
{
    for (int i = 1; i <= n; i++)
    {
        dis[i] = INF;
    }
}

void addedge(int u, int v, int d) //to imitate Linkedlist by Array
{
    addcnt++;
    e[addcnt].next = head[u];
    e[addcnt].to = v;
    e[addcnt].dis = d;
    head[u] = addcnt;
}

void prim()
{
    dis[1] = 0;
    hp.push({0, 1});
    while (!hp.empty() && cnt < n)
    {
        int p = hp.top().pos;
        int d = hp.top().dis;
        hp.pop();
        if (visited[p]) continue;
        visited[p] = 1;
        ans += d;
        cnt++;
        for (int i = head[p]; i != 0; i = e[i].next)
        {
            int dest = e[i].to;
            if (dis[dest] > e[i].dis)
            {
                dis[dest] = e[i].dis;
                if (!visited[dest]) hp.push({dis[dest], dest});
            }
        }
    }
    cnt == n ? cout << ans << "\n" : cout << "orz\n";
}

int main(void)
{

#ifdef DEBUG
    freopen("testdata.in", "r", stdin);
#endif

    cin >> n >> m;
    _init();
    for (int i = 1; i <= m; i++)
    {
        int u, v, d;
        cin >> u >> v >> d;
        addedge(u, v, d);
        addedge(v, u, d);
    }
    prim();
    return 0;
}
