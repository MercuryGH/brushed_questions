/**
 * https://www.acwing.com/solution/content/91517/
 * 双指针，枚举连续区间，时间复杂度O(sqrt(n) * sqrt(n))空间复杂度O(1)
 * 然而居然有一个点超时，估计是要剪枝了。懒得剪
 */

#include <vector>
#include <unordered_set>
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
using std::vector, std::string;

void getMaxConsecutiveFactors(int &ansStartIndex, int &ansLen, const int n)
{
    for (int i = 2; i * i <= n; i++)
    {
        int acc = 1;
        int j = i;
        while (true)
        {
            acc *= j;
            if (n % acc != 0)
            {
                break;
            }
            j++;
        }
        if (j - i > ansLen)
        {
            ansLen = j - i;
            ansStartIndex = i;
        }
    }
}

int main()
{
    int n;
    std::cin >> n;

    int ansLen = 0;
    int ansStartIndex = 0;
    getMaxConsecutiveFactors(ansStartIndex, ansLen, n);

    if (ansLen == 0)
    {
        std::cout << "1\n"
                  << n;
        return 0;
    }

    std::cout << ansLen << "\n";
    for (int i = 0; i < ansLen; i++)
    {
        std::cout << ansStartIndex + i;
        if (i != ansLen - 1)
        {
            std::cout << "*";
        }
    }
    return 0;
}