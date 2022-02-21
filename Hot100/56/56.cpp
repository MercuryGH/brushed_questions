#include <vector>
#include <algorithm>
using std::vector;

/**
想到排序就简单了。确实只能排序做。
*/
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        const int n = intervals.size();
        if (n == 0) {
            return {};
        }
        std::sort(intervals.begin(), intervals.end());
        vector<vector<int>> merged;

        for (int i = 0; i < n; i++) {
            const int l = intervals[i][0];
            const int r = intervals[i][1];
            if (merged.size() == 0) {
                merged.push_back({l, r});  // 第一个区间
                continue;
            }

            const int rightest = merged.back()[1];  // 当前区间集的最右端
            if (rightest < l) {  // 新的区间
                merged.push_back({l, r});
            }
            else {
                merged.back()[1] = std::max(rightest, r);  // 更新已有的区间（可以合并）
            }
        }
        return merged;
    }
};
