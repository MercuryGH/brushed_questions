class Solution
{
public:
    int reachNumber(int target)
    {
        if (target < 0)
        {
            target = -target;
        }

        int sum = 0;
        for (int i = 1; ; i++)
        {
            sum += i;
            if (sum >= target)
            {
                if ((sum - target) % 2 == 0)
                {
                    return i;
                }
            }
        }

        return -1;
    }
};