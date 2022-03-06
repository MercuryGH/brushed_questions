#include <unordered_map>
#include <vector>
#include <iostream>
using std::vector;

class Solution
{
public:
    int mostFrequent(vector<int> &nums, int key)
    {
        const int n = nums.size();
        int keyIndex = 0;
        for (int i = 0; i < n; i++)
        {
            if (nums[i] == key)
            {
                keyIndex = i;
                break;
            }
        }

        std::unordered_map<int, int> hash;
        int ans = -1;
        int maxFreq = 0;
        for (int i = keyIndex; i < n - 1; i++)
        {
            if (nums[i] == key)
            {
                hash[nums[i + 1]]++;
                if (hash[nums[i + 1]] > maxFreq)
                {
                    ans = nums[i + 1];
                    maxFreq = hash[nums[i + 1]];
                }
            }
        }

        return ans;
    }
};

int main()
{
    Solution s;
    std::cout << s.mostFrequent({11, 22, 11, 33, 11, 33, 11}, 11) << "\n";
}