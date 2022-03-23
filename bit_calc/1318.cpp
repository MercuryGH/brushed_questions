/**
 * 或运算的最小翻转次数
 * 位运算模拟题
 */
class Solution
{
    // 获取 x 的低 k 位的值 （k从0数起）
    static bool getKthLowbit(int x, int k)
    {
        return (x >> k) & 1;
    }
public:
    int minFlips(int a, int b, int c)
    {
        int ans = 0;
        for (int i = 0; i < 31; i++)
        {
            const bool curBitA = getKthLowbit(a, i);
            const bool curBitB = getKthLowbit(b, i);
            const bool curBitC = getKthLowbit(c, i);
            if (curBitC == 0) { // all set to zero
                ans += (curBitA == 1) + (curBitB == 1);
            } else { // only one need to set to one
                ans += (curBitA == 0 && curBitB == 0);
            }
        }
        return ans;
    }
};