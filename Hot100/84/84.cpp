#include <vector>
#include <stack>
#include <algorithm>
using std::vector;

class Solution {
public:
    int largestRectangleArea(vector<int> &heights) {
        heights.insert(heights.begin(), 0); // 方便扩散的处理
        heights.push_back(0); // 同上

        const int n = heights.size();
        std::stack<int> s;

        int ans = 0;
        for (int i = 0; i < n; i++) {
            while (s.empty() == false && heights[i] < heights[s.top()]) { // 必须加 s.empty() == false 
                const int topElement = s.top();
                s.pop();
                const int leftLessIndex = s.top() + 1; // 开区间左端点为 s.top()，因此闭区间左端点为 s.top() + 1
                const int rightLessIndex = i - 1; // 开区间右端点为 i，因此闭区间右端点为 i - 1
                const int area = (rightLessIndex - leftLessIndex + 1) * heights[topElement];
                ans = std::max(ans, area);
            }
            s.push(i);
        }
        return ans;
    }
};
