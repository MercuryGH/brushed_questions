#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::vector, std::string;

class Solution
{
    bool check(const vector<int> &nums, int mid)
    {
        if (nums[mid] == mid)
        { // left
            return true;
        }
        return false;
    }

public:
    int missingNumber(vector<int> &nums) // nums is sorted
    {
        const int n = nums.size();
        int l = 0;
        int r = n - 1;
        int ans = 0;
        while (true)
        {
            if (l > r)
            {
                break;
            }

            const int mid = (l + r) / 2;
            if (check(nums, mid))
            {
                l = mid + 1;
                ans = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        return ans;
    }
};

int main()
{
    bool b = false;
    vector<bool> vs = {b, b, b, b, b, b};
    vector<int> vv = {b, b, b, b, b, b};
    std::cout << sizeof(vs) << " " << sizeof(vv) << "\n";

    return 0;
}