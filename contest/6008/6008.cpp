#include <iostream>
#include <vector>
#include <string>
using std::vector, std::string;

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

    bool check(const vector<int> &time, const int mid, const int totalTrips) {
        int ans = 0;
        for (const int t : time) {
            ans += mid / t;
        }
        return ans >= totalTrips;
    }

public:
    long long minimumTime(vector<int> &time, int totalTrips)
    {
        const int n = time.size();
        std::vector<Bus> buses;
        for (const int t : time) {
            buses.push_back(Bus(t));
        }

        int l = 1;
        int r = totalTrips;
        int ans = 1;
        while (true) {
            if (l > r) {
                break;
            }
            if (l == r) {
                ans = l; 
                break;
            }

            const int mid = (l + r) / 2;
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
    vector<int> time = {1, 2, 3};
    int totalTrips = 5;
    std::cout << s.minimumTime(time, totalTrips) << "\n";

    return 0;
}