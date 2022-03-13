#include <vector>
#include <string>
using std::vector, std::string;

/**
 * 旋转矩阵
 * 模拟题
 * 如果不想要额外空间，可以用“改变边界”的方式省去 vis 数组
 */
class Solution {
    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int n, m;
    bool outOfBound(int x, int y) {
        return x < 0 || x >= n || y < 0 || y >= m;
    }
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        n = matrix.size();
        m = matrix[0].size();
        vector<int> ans;
        vector<vector<bool>> vis(n, vector<bool>(m, false));

        int dirCtrl = 0;
        int x = 0; 
        int y = 0;
        while (true) {
            ans.push_back(matrix[x][y]);
            vis[x][y] = true;
            for (int i = dirCtrl; ; i = (i + 1) % 4) {
                const int dx = dir[i][0];
                const int dy = dir[i][1];
                if (outOfBound(x + dx, y + dy) == false && vis[x + dx][y + dy] == false) {
                    dirCtrl = i;
                    x += dx;
                    y += dy;
                    break;
                }

                if ((i + 1) % 4 == dirCtrl) {
                    goto END;
                }
            }
        }
        END:
        return ans;
    }
};