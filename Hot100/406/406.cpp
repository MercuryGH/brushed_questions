#include <vector>
#include <algorithm>
using std::vector;

/**
 * 根据身高重建队列
 * 思路：从低到高，依次填坑。
 * 普普通通 O(n^2) 算法
 */
class Solution
{
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>> &people)
    {
        const auto cmp = [](const vector<int> &u, const vector<int> &v) {
            if (u[0] < v[0]) {
                return true;
            }
            return u[0] == v[0] && u[1] > v[1];
        };
        std::sort(people.begin(), people.end(), cmp);

        const int n = people.size();
        vector<vector<int>> ans(n);
        for (const auto &person : people) {
            const int pitIndex = person[1]; // 填坑位置
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                if (ans[i].empty() == true) { // 没人占坑
                    if (cnt == pitIndex) { // 恰好够
                        ans[i] = person; // 占坑
                        break;
                    }
                    cnt++;
                }
            }
        }
        return ans;
    }
};

