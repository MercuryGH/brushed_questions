#include <algorithm>

/**
 * 多路归并（多指针）解法，要点是去重
 * 看代码很容易理解
 */
class Solution
{
    static int min3(int a, int b, int c) {
        return std::min(a, std::min(b, c));
    }
public:
    int nthUglyNumber(int n)
    {
        int *uglyNums = new int[n + 1];
        uglyNums[1] = 1;

        for (int x = 1, y = 1, z = 1, i = 2; i <= n; i++) {
            int a = uglyNums[x] * 2;
            int b = uglyNums[y] * 3;
            int c = uglyNums[z] * 5;

            int nextMin = min3(a, b, c);
            if (nextMin == a) {
                x++;
            } // 注意，下面的不能改成 else if ，否则重复
            if (nextMin == b) {
                y++;
            } 
            if (nextMin == c) {
                z++;
            }
            uglyNums[i] = nextMin;
        }
        int ans = uglyNums[n];
        delete[] uglyNums;
        return ans;
    }
};