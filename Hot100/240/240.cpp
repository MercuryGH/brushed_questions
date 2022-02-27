#include <vector>
using std::vector;

/**
 * 搜索二维矩阵 II
 * 从右上角开始搜的话，立马变成二叉搜索树的题目了。时间复杂度为 O(n + m)
 */
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        const int n = matrix.size();
        const int m = matrix[0].size();

        int i = 0;
        int j = m - 1;
        while (true) {
            if (i >= n || j < 0) {
                break;
            }

            const int curNum = matrix[i][j];

            if (curNum == target) {
                return true;
            }
            if (curNum > target) {
                j--;
            } else {
                i++;
            }
        }
        return false;
    }
};
