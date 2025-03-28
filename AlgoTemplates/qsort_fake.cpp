#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

typedef int ElementType;

int n, m, a[] = {1, 4, 23, 3, 0, -1};

void printArray()
{
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << "\n";
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


void my_qsort(int a[], int l, int r)  // 这其实不是快速排序，而是二分冒泡排序
{
    int pivot = a[l];  // pivot = median(a[l], a[mid], a[r]) 在实践中有用
    int i = l, j = r;
    do {
        while (a[i] < pivot) i++;  // 注意 < 不是 <=
        while (a[j] > pivot) j--;
        if (i <= j)
        {
            swap(&a[i], &a[j]);  // 一次swap()消除至少两个逆序对
            i++;
            j--;
        }
    } while (i <= j);

    cout << "l = " << l << " r = " << r << " i = " << i << " j = " << j << "\n";
    printArray();

    if (l < j) my_qsort(a, l, j);
    if (i < r) my_qsort(a, i, r);
}

int main(void)
{
    n = 6;
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << "\n";
    my_qsort(a, 0, n - 1);

    return 0;
}

