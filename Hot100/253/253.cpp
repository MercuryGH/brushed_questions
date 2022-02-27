#include <vector>
#include <algorithm>
using std::vector;

class Solution
{
public:
    int minMeetingRooms(vector<vector<int>> &intervals)
    {
        const auto cmp = [](const auto &p1, const auto &p2) {
            if (p1.first == p2.first) {
                return p1.second < p2.second;
            }
            return p1.first < p2.first;
        };

        const int n = intervals.size();
        vector<std::pair<int, int>> times;
        for (const auto &interval : intervals) {
            times.push_back({ interval[0], 1 }); // 会议开始的 .second 记为 1
            times.push_back({ interval[1], -1 }); // 会议结束的 .second 记为 -1
        }
        std::sort(times.begin(), times.end(), cmp);

        int maxOverlap = 0;
        int curOverlap = 0;
        for (const auto &time : times) {
            curOverlap += time.second;
            maxOverlap = std::max(maxOverlap, curOverlap);
        }

        return maxOverlap;
    }
};