#include <vector>
#include <algorithm>
#include <ctime>
using std::vector;

class Solution
{
    // 获取 [l, r] 中的均匀随机数
    static int getRandomNumber(int l, int r)
    {
        return rand() % (r - l + 1) + l;
    }

    // 将nums通过 nums[返回值] 分割成小、大两部分
    int randomizedGetPartition(vector<int> &nums, int l, int r)
    {
        const int randomIndex = getRandomNumber(l, r);
        std::swap(nums[l], nums[randomIndex]); // 钦定 pivot = nums[l]

        const int pivot = nums[l];

        int ptr = l; // ptr 始终指向最右边的 <= pivot 的数
        for (int i = l + 1; i <= r; i++)
        {
            if (nums[i] <= pivot)
            {
                ptr++;
                std::swap(nums[ptr], nums[i]);
            }
        }
        std::swap(nums[ptr], nums[l]);
        return ptr;
    }

    // 快速（随机化）
    void quickSort(vector<int> &nums, int l, int r)
    {
        if (l >= r)
        {
            return;
        }

        int pos = randomizedGetPartition(nums, l, r);
        quickSort(nums, l, pos - 1);
        quickSort(nums, pos + 1, r);
    }

    // 归并
    void mergeSort(vector<int> &nums, int l, int r) {
        divide(nums, l, r);
    }

    void divide(vector<int> &nums, int l, int r) {
        if (l >= r) {
            return;
        }

        const int mid = (l + r) / 2;
        divide(nums, l, mid);
        divide(nums, mid + 1, r);
        merge(nums, l, mid, r);
    }

    vector<int> tmp;
    /**
     * 将nums[]数组的两个有序子数组nums[l : mid], nums[mid + 1, r]（闭区间）合并
     */
    void merge(vector<int> &nums, int l, int mid, int r) {
        int i = l;
        int j = mid + 1;
        int cnt = 0;
        while (true) {
            if (i > mid || j > r) {
                break;
            }

            if (nums[i] <= nums[j]) {
                tmp[cnt++] = nums[i++];
            } else {
                tmp[cnt++] = nums[j++];
            }
        }
        while (i <= mid) {
            tmp[cnt++] = nums[i++];
        }
        while (j <= r) {
            tmp[cnt++] = nums[j++];
        }

        for (int i = 0; i < r - l + 1; i++) {
            nums[l + i] = tmp[i];
        }
    }

    /**
     * 堆排序
     * 建立大顶堆
     * nums[0] 预先用pivot填上
     */ 
    void percolateDown(vector<int> &nums, int cur, int size) {
        while (true) {
            const int lSon = cur * 2;
            const int rSon = cur * 2 + 1;
            const bool hasLSon = lSon <= size;
            const bool hasRSon = rSon <= size;

            int largeIndex = cur;
            if (hasLSon) {
                if (nums[largeIndex] < nums[lSon]) {
                    largeIndex = lSon;
                }
            }
            if (hasRSon) {
                if (nums[largeIndex] < nums[rSon]) {
                    largeIndex = rSon;
                }
            }

            if (largeIndex == cur) { // 到底了，或者下面的都是小的
                return;
            }
            std::swap(nums[cur], nums[largeIndex]);
            cur = largeIndex; // 继续迭代
        }
    }
    void buildMaxHeap(vector<int> &nums, int size) {
        for (int i = size / 2; i >= 1; i--) {
            percolateDown(nums, i, size);
        }
    }
    void heapSort(vector<int> &nums, int n) {
        nums.insert(nums.begin(), INT_MAX);

        buildMaxHeap(nums, n);
        // 不断将 max pop 到数组的最后面。这样就能实现从小到大排序了
        for (int i = n; i >= 2; i--) {
            std::swap(nums[i], nums[1]);
            percolateDown(nums, 1, i - 1); // 注意确定位置之后，堆的大小要 -1
        }

        std::move(nums.begin() + 1, nums.end(), nums.begin());
        nums.resize(n);
    }

public:
    vector<int> sortArray(vector<int> &nums)
    {
        srand((unsigned)time(NULL));
        const int n = nums.size();

        // quickSort(nums, 0, n - 1);
        // return nums;

        // tmp.resize(n, 0);
        // mergeSort(nums, 0, n - 1);
        
        heapSort(nums, n);

        return nums;
    }
};

/*

 */
