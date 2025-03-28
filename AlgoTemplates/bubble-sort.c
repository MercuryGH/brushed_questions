#include<stdio.h>
#include<string.h>
#include<stdbool.h>

int n;
int a[110];

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int main(void)
{

#ifdef DEBUG
	freopen("ZJUtestdata.in", "r", stdin);
#endif

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 2; i <= n; i++)
	{
		for (int j = 1; j <= i - 1; j++)
		{
			if (a[j] > a[i]) swap(&a[j], &a[i]);  // 一般是相邻原始交换a[j] > a[j + 1]。这是另一种版本
		}
	}
	for (int i = 1; i <= n; i++) printf("%d ", a[i]);
	return 0;
}