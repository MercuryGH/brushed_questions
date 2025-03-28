#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;

int n, m, s;
int head[100010], dis[100010], cnt;
bool visited[100010];
struct edge
{
    int next, to, dis;
} e[500010];
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
    cnt++;
    e[cnt].next = head[u];
    e[cnt].to = v;
    e[cnt].dis = d;
    head[u] = cnt;
}

void dijkstra()
{
    dis[s] = 0;
    hp.push({0, s}); //dis=0,pos=s
    while (!hp.empty())
    {
        node tmp = hp.top();
        hp.pop();
        int p = tmp.pos;
        if (visited[p]) continue;
        visited[p] = 1;
        for (int i = head[p]; i != 0; i = e[i].next)
        {
            int dest = e[i].to;
            if (dis[dest] > dis[p] + e[i].dis)
            {
                dis[dest] = dis[p] + e[i].dis;
                if (!visited[dest])
                {
                    hp.push({dis[dest], dest});
                }
            }
        }
    }
}

int main(void)
{

#ifdef DEBUG
    freopen("testdata.in", "r", stdin);
#endif

    cin >> n >> m >> s;
    _init();
    for (int i = 1; i <= m; i++)
    {
        int u, v, d;
        cin >> u >> v >> d;
        addedge(u, v, d);
    }
    dijkstra();
    for (int i = 1; i <= n; i++)
    {
        cout << dis[i] << " ";
    }
    return 0;
}
