#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using std::vector;
using std::string;

class Solution
{

    struct Bus
    {
        int efficency;
        Bus(int efficency): efficency(efficency) {}
        int multiply(int time)
        {
            int result = time / efficency;
            return result;
        }
    };

    bool check(const vector<int> &time, const long long mid, const int totalTrips) {
        long long ans = 0;
        for (const int t : time) {
            ans += mid / t;
        }
        return ans >= totalTrips;
    }

public:
    long long minimumTime(vector<int> &time, int totalTrips)
    {
        // const int n = time.size();
        const long long maxTime = *std::max_element(time.begin(), time.end());

        long long l = 1;
        long long r = maxTime * totalTrips;
        long long ans = 1;
        while (true) {
            if (l > r) {
                break;
            }
            if (l == r) {
                ans = l; 
                break;
            }

            const long long mid = (r - l) / 2 + l;
            if (check(time, mid, totalTrips)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }
};

int main() {
    Solution s;
    vector<int> time = {10000000};
    int totalTrips = 10000000; 
    std::cout << s.minimumTime(time, totalTrips) << "\n";

    return 0;
}