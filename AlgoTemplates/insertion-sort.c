#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#define INF 0x3f3f3f3f

int n;
int a[110];

void swap(int *a,int *b)
{
	int tmp=*a;
	*a=*b;
	*b=tmp;
}

int main(void)
{

#ifdef DEBUG
	freopen("ZJUtestdata.in","r",stdin);
#endif

	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	a[0]=-INF; //否则没法排负数
	for (int i=2;i<=n;i++)
	{
		int tmp=a[i],j;
		for (j=i;j>=1 && a[j-1]>tmp;j--)
		{
			a[j]=a[j-1];
		}
		a[j]=tmp;
	}
	for (int i=1;i<=n;i++) printf("%d ",a[i]);
	return 0;
}