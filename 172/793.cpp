int preimageSizeFZF(int K)
{
    int step = 0;
    while (step < K)
        step = step * 5 + 1;

    while (K)
    {
        step = (step - 1) / 5;
        if (K / step == 5)
            return 0;
        K %= step;
    }
    return 5;
}

#include <cmath>

class Solution {
public:
    int preimageSizeFZF(int k) {
        int acc = 0;
        while (acc < k) {
            acc *= 5;
            acc += 1;
        }

        int cur = k;
        while (cur > 0) {
            acc -= 1;
            acc /= 5;
            if (cur / acc >= 5) {
                return 0;
            }
            cur %= acc;
        }
        return 5;
    }
};