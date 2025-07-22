#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int n;
int a[100010];

typedef int ElementType;

void printArray()
{
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void swap(int *a, int *b)  // C风格swap函数
{
    int tmp = *a;  
    *a = *b;
    *b = tmp;
}

// 将nums通过 nums[返回值] 分割成小、大两部分
int randomizedGetPartition(vector<int>& nums, int l, int r)
{
    const int randomIndex = getRandomNumber(l, r);
    std::swap(nums[l], nums[randomIndex]); // 钦定 pivot = nums[l]

    const int pivot = nums[l];  // pivot随机选取，或者直接选取最左边的元素

    int ptr = l; // ptr 始终指向最右边的 <= pivot 的数
    // 将数组调整成 pivot, [<=pivot], ptr, [>pivot]
    for (int i = l + 1; i <= r; i++)
    {
        if (nums[i] <= pivot)
        {
            ptr++;
            std::swap(nums[ptr], nums[i]);
        }
    }
    // 将数组调整成 [<=pivot], pivot, [>pivot]
    std::swap(nums[ptr], nums[l]);
    return ptr;
}

int getPartition(int a[], int l, int r)  // 获取快速排序的分段位置
{
    int pivot = a[l];  // pivot直接选取最左边的元素，或者随机
    int i = l, j = r;  // 两个index指针
    while (1)  // 循环直至 i >= j，即相遇
    {
        while (i < j && pivot <= a[j])
            j--;
        while (i < j && pivot >= a[i])
            i++;
        if (i < j)
            swap(&a[i], &a[j]);  // 保证pivot左边的小，右边的大
        else
            break;
    }
    swap(&a[i], &a[l]);  // pivot到达其位置
    return i;  // 返回pivot位置
}
void quickSort(int a[], int l, int r)  // 快速排序原始版本
{
    if (l >= r) return;  // 分到极限了

    int partition = getPartition(a, l, r);  // 获取分段位置

    quickSort(a, l, partition - 1);  // 左边递归快排
    quickSort(a, partition + 1, r);  // 右边递归快排
}
int main(void)
{

#ifdef DEBUG
    freopen("ZJUtestdata.in", "r", stdin);
#endif

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    printArray();
    quickSort(a, 1, n);
    for (int i = 1; i <= n; i++) printf("%d ", a[i]);
    return 0;
}