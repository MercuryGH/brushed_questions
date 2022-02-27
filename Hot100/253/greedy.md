# 活动选择问题——房间版

给定$n$个活动，第$i$个活动$a_i$计划在时间区间$[s_i,f_i)$内进行。记$A_n= \{a_1,a_2,\dots,a_n\}$。

我们称活动$i,j$是冲突的，当且仅当$s_i \geq f_j$或$s_j \geq f_i$。

现在有多个活动地点，如何安排这些活动，使得所有活动都能进行，且使用的活动地点的个数最小化？

## 贪心策略1

先在一个地点中尽可能地安排多的活动；从活动列表中删除这些活动，然后递归地在另一个地点中尽可能地安排多的活动，直到活动列表为空。

会错！容易举出反例。

## 贪心策略2

将所有活动按$s_i$排序，然后为最早进行的活动$a_1$安排$1$号房间，并把$1$号房间纳入已安排的的房间列表；

`for i = 2 to n`，若$a_i$能在当前已安排的的房间列表中进行，则将$a_i$安排至那个房间；否则，为$a_i$安排一个新的房间，并把该房间纳入已安排的的房间列表。

对了！证明如下：

显然贪心策略的第一个选择必然与任意最优解相容，因为所有事件必须被安排，所以任意最优解必然在某个房间安排了该活动。

记$a_{es}$是贪心策略从$A_n$选出的第二个活动，这个活动必然存在于任意最优解的某个房间中。若

1. 贪心策略和最优解都把$a_{es}$安排到同一房间，则两者相容；
2. 贪心策略和最优解把$a_{es}$安排到不同房间，即贪心策略没有为$a_{es}$
   开辟新的房间——此时贪心策略用到的房间数甚至暂时比那个最优解少$1$个，而且贪心策略随时可以开辟新的房间，以处理未来可能的活动。所以贪心策略仍与最优解相容。

于是，无论是哪种情况，都可以将问题的规模降低$1$。递归地往下，直到问题规模恰好为$1$，此时贪心策略显然成立。故贪心策略的正确性得证。

### 优化

我们不必每次都判断是否与已经安排的活动冲突。

首先，将每个活动按照$s_i$排序，如果$s_i$相同，则$e_i$小的优先。

然后，扫描时间段$[\min(s_i), \max(s_i)]$内的所有时间端点。若扫描到了$s_j$，则安排该活动；若扫描到了$e_j$，则撤销该活动。如此即可最小化活动个数的地点。

## 代码实现

由于我们只需要输出最小的活动地点的数目，因此，在将所有活动排序后，我们从早到晚按时间轴枚举每个活动开始、结束的时间点：

* 若枚举到了活动开始的时间点，则立即安排该活动，并且记overlap数 +1；
* 若枚举到了活动结束的时间点，则立即撤销该活动，并且记overlap数 -1。

最终答案，即为在该过程中，所到达的最大overlap数。

```cpp
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
```

时间复杂度为$O(n \log n)$（排序），空间复杂度为$O(n)$。
