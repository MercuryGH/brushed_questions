#include <iostream>
#include <numeric>
#include <vector>
using std::vector;

int n, m;

/**
 * ICPC真题（仅k = m） https://www.luogu.com.cn/problem/P6122
 * 贪心 O(n) 错解，但对于弱数据而言能AC
 */
class Solution {
public:
    int getMinimumScheduleDistance(vector<int> &rooms, vector<int> &initPositions) {
        int roomsSum = std::accumulate(rooms.begin(), rooms.end(), 0) - m;
        for (const int position : initPositions) {
            rooms[position]--;
        }

        int ans = 0;
        for (int i = n; i > 1; i--) {
            if (rooms[i] != 0) {
                if (roomsSum > 0 && rooms[i] > 0) {
                    if (roomsSum > rooms[i]) {
                        roomsSum -= rooms[i];
                    } else {
                        rooms[i / 2] += (rooms[i] - roomsSum);
                        ans += (rooms[i] - roomsSum);
                        rooms[i] = 0;
                    }
                    continue;
                }
                rooms[i / 2] += rooms[i];
                ans += std::abs(rooms[i]);
                rooms[i] = 0;
            }
        }
        return ans;
    }
};

int main() {
    std::cin >> n >> m;
    vector<int> rooms(n + 1);
    vector<int> initPositions(m);

    for (int i = 1; i <= n; i++) {
        std::cin >> rooms[i];
    }
    for (int i = 0; i < m; i++) {
        std::cin >> initPositions[i];
    }

    Solution s;
    int ans = s.getMinimumScheduleDistance(rooms, initPositions);

    std::cout << ans << "\n";
    return 0;
}