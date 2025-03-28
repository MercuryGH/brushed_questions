#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

struct edge
{
	int s, e, v;
} ed[200010];
int n, m, sum, cnt, set[5010];

bool cmp(edge a, edge b)
{
	return a.v < b.v;
}
void init()
{
	for (int i = 1; i <= n; i++) set[i] = i;
}
int find(int x)
{
	return x == set[x] ? x : set[x] = find(set[x]);
}

void kruskal()
{
	init();
	for (int i = 1; i <= m; i++)
	{
		int tmp1 = find(ed[i].s);
		int tmp2 = find(ed[i].e);
		if (tmp1 != tmp2)
		{
			set[tmp1] = tmp2;
			sum += ed[i].v;
			cnt++;
			if (cnt == n - 1) break;
		}
	}
	cnt < n - 1 ? cout << "orz" : cout << sum;
	return;
}

int main(void)
{

#ifdef DEBUG
	freopen("testdata.in", "r", stdin);
#endif

	cin >> n >> m;
	for (int j = 1; j <= m; j++)
	{
		cin >> ed[j].s >> ed[j].e >> ed[j].v;
	}
	sort(ed + 1, ed + m + 1, cmp);

	kruskal();

	return 0;
}