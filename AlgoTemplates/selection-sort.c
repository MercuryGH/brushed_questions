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
	for (int i = 1; i <= n; i++)
	{
		int index = i;
		for (int j = i + 1; j <= n; j++)
		{
			if (a[j] < a[index]) index = j;
		}
		swap(&a[index], &a[i]);
	}
	for (int i = 1; i <= n; i++) printf("%d ", a[i]);
	return 0;
}