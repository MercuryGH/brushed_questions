#include <algorithm>
#include <stack>
#include <vector>
using std::vector;

class Solution
{
    int largestRectangleArea(const vector<int> &heights)
    {
        const int n = heights.size() + 2;
        vector<int> pivotedHeights(n);
        pivotedHeights[0] = 0;
        pivotedHeights[n - 1] = 0;
        std::copy(heights.begin(), heights.end(), pivotedHeights.begin() + 1);

        std::stack<int> s;

        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            while (s.empty() == false && pivotedHeights[i] < pivotedHeights[s.top()])
            { // 必须加 s.empty() == false
                const int topElement = s.top();
                s.pop();
                const int leftLessIndex = s.top() + 1; // 开区间左端点为 s.top()，因此闭区间左端点为 s.top() + 1
                const int rightLessIndex = i - 1;      // 开区间右端点为 i，因此闭区间右端点为 i - 1
                const int area = (rightLessIndex - leftLessIndex + 1) * pivotedHeights[topElement];
                ans = std::max(ans, area);
            }
            s.push(i);
        }
        return ans;
    }

public:
    int maximalRectangle(vector<vector<char>> &matrix)
    {
        const int n = matrix.size();
        const int m = matrix[0].size();
        vector<int> heights(m);

        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (matrix[i][j] == '1')
                {
                    heights[j]++;
                }
                else
                {
                    heights[j] = 0;
                }
            }
            ans = std::max(ans, largestRectangleArea(heights));
        }
        return ans;
    }
};

