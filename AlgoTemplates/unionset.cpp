#include <bits/stdc++.h>

using namespace std;

int uset[10010];
int i;

void makeset(int size)
{
    for (i = 1; i <= size; i++)
        uset[i] = i;
}

int find(int x)
{
    // if (x != uset[x])
    //  uset[x] = find(uset[x]);

    // return uset[x];

    return x == uset[x] ? uset[x] : (uset[x] = find(uset[x]));
}

void unionset(int x, int y)
{
    uset[find(x)] = find(y);
}

int main(void)
{
//  freopen("test.txt","r",stdin);
    int n, m, zi, xi, yi;
    cin >> n >> m;
    makeset(n);
    for (i = 1; i <= m; i++)
    {
        cin >> zi >> xi >> yi;
        if (zi == 1)
        {
            unionset(xi, yi);
        }
        else
        {
            if (find(xi) == find(yi))
                cout << "Y\n";
            else 
                cout << "N\n";
        }
    }
    return 0;
}