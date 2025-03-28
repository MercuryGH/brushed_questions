#include <iostream>
#include <cstdio>
#include <set>
#define MAXN 100010
using namespace std;

int n, m;
char z;
int x, y;
int union_set[MAXN];
int a[MAXN];
set <int> s;

void init()
{
    for (int i = 1; i <= n; i++)
        union_set[i] = -1;
}

int find(int x)
{
    return union_set[x] < 0 ? x : union_set[x] = find(union_set[x]);
}

void Union(int x, int y)
//按大小合并
{
    int root_x = find(x);
    int root_y = find(y);

    if (union_set[root_x] >= union_set[root_y])
    {
        union_set[root_y] += union_set[root_x];
        union_set[root_x] = root_y;
    }
    else if (union_set[root_x] < union_set[root_y])
    {
        union_set[root_x] += union_set[root_y];
        union_set[root_y] = root_x;
    }
}

int main(void)
{

#ifdef DEBUG
    freopen("testdata.in", "r", stdin);
#endif

    cin >> n;
    init();
    cin >> z;
    while (z != 'S')
    {
        cin >> x >> y;
        switch (z)
        {
            case 'I': 
            {
                Union(x, y); 
                break;
            }
            case 'C': 
            {
                find(x) == find(y) ? cout << "yes" : cout << "no";
                cout << "\n"; 
                break;
            }
        }
        cin >> z;
    }
    for (int i = 1; i <= n; i++)
    {
        s.insert(find(i));
    }
    int cnt = s.size();
    if (cnt == 1) cout << "The network is connected.\n";
    else cout << "There are " << cnt << " components.\n";
    return 0;
}