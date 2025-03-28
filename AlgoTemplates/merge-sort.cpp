int t[100010];
void merge_sort(int a[], int l, int r)
{
    int mid = (l + r) / 2;
    if (l < mid) merge_sort(a, l, mid);
    if (mid + 1 < r) merge_sort(a, mid + 1, r);
    
    // Below are Merge()
    int i = l, k = l, j = mid + 1;
    // i == Lpos(左指针), j == Rpos, mid == LeftEnd(左序列结束位置), r == RightEnd 
    while (i <= mid && j <= r)
    {
        if (a[i] <= a[j]) 
            t[k++] = a[i++];
        else 
            t[k++] = a[j++];
    }
    while (i <= mid) 
        t[k++] = a[i++];
    while (j <= r) 
        t[k++] = a[j++];
    for (int i = l; i <= r; i++) 
        a[i] = t[i];
}

/*Iterative Version*/
void merge_sort( ElementType list[], int N )
{
    ElementType extra[MAXN];  /* the extra space required */
    int length = 1;  /* current length of sublist being merged */
    while ( length < N ) 
    { 
        merge_pass( list, extra, N, length ); /* merge list into extra */
        output( extra, N );
        length *= 2;
        merge_pass( extra, list, N, length ); /* merge extra back to list */
        output( list, N );
        length *= 2;
    }
} 
void merge_pass( ElementType list[], ElementType sorted[], int N, int length )
{
    int k = 0;
    for (int ptr2Cur = 0; ptr2Cur < N; ptr2Cur += length * 2)
    {
        int i = ptr2Cur;
        int j = ptr2Cur + length;
        int mid = ptr2Cur + length;
        int r = ptr2Cur + length * 2;
        while (i < mid && j < r && i < N && j < N)
        {
            if (list[i] < list[j]) 
                sorted[k++] = list[i++];
            else 
                sorted[k++] = list[j++];
        }
        while (i < mid && i < N)
        {
            sorted[k++] = list[i++];
        }
        while (j < r && j < N)
        {
            sorted[k++] = list[j++];
        }
    }
}

// 逆序对版本
int t[MAXN];
void mergesort(int a[], int l, int r)
{
    int mid = (l + r) / 2;
    if (l < mid) 
        mergesort(a, l, mid);
    if (mid + 1 < r) 
        mergesort(a, mid + 1, r);
    int i = l, k = l, j = mid + 1;
    while (i <= mid && j <= r)
    {
        if (a[i] <= a[j]) 
            t[k++] = a[i++];
        else 
        {
            ans += mid - i + 1;
            t[k++] = a[j++]; //统计逆序对
        }
    }
    while (i <= mid)
        t[k++] = a[i++];
    while (j <= r) 
        t[k++] = a[j++];
    for (int i = l; i <= r; i++) 
        a[i] = t[i];
}

int main(void)
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    merge_sort(a, 1, n);  
    for (int i = 1; i <= n; i++) printf("%d ", a[i]);
    return 0;
}