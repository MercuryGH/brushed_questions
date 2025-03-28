#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int n;
int a[100010];

typedef int ElementType;

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void printArray()
{
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

ElementType Median3(ElementType a[], int l, int r)
{
    int mid = (l + r) / 2;
    if (a[l] > a[mid])
        swap(&a[l], &a[mid]);
    if (a[l] > a[r])
        swap(&a[l], &a[r]);
    if (a[mid] > a[r])
        swap(&a[mid], &a[r]);

    swap(&a[mid], &a[r - 1]);  // 把 pivot 放在倒数第二个位置
    // 只需排序A[l + 1] 至 A[r - 2]
    printArray();
    return a[r - 1];
}

int getPartition(ElementType a[], int l, int r)
{
    ElementType pivot = Median3(a, l, r);
    int i = l, j = r - 1;  
    while (1)
    {
        while (i < j && a[++i] < pivot);
        while (i < j && a[++j] > pivot);
        if (i < j)
            swap(&a[i], &a[j]);
        else
            break;
    }
    swap(&a[i], &a[r - 1]); 
    return i;
}

void quickSort(ElementType a[], int l, int r)  // qSort 原始版本
// 这个版本是错的。如果一定要用Median3策略，就一定要在适当的时候转插入排序。
{
    if (l >= r) return;

    ElementType partition = getPartition(a, l, r);

    quickSort(a, l, partition - 1);
    quickSort(a, partition + 1, r);
}

int main(void)
{

#ifdef DEBUG
    freopen("ZJUtestdata.in", "r", stdin);
#endif

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]); printArray();
    quickSort(a, 1, n);
    for (int i = 1; i <= n; i++) printf("%d ", a[i]);
    return 0;
}