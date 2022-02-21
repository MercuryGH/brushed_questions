#include <unordered_map>

class DetectSquares {
    std::unordered_map<int, std::unordered_map<int, int>> cntX;  // key: x, value: (key: y, value: 坐标为(x, y)的点的个数)
    std::unordered_map<int, std::unordered_map<int, int>> cntY;  // key: y, value: (key: x, value: 坐标为(x, y)的点的个数)
public:
    DetectSquares() {
    }
    
    void add(std::vector<int> point) {
        const int x = point[0];
        const int y = point[1];
        this->cntX[x][y]++;
        this->cntY[y][x]++;
    }
    
    int count(std::vector<int> point) {
        const int x0 = point[0];
        const int y0 = point[1];

        int ans = 0;
        for (auto yC : cntX[x0]) {  // 具有相同 x 坐标的点的 y - cnt 对
            const int x1 = x0;
            const int y1 = yC.first;
            const int x1y1PointNums = yC.second;
            const int edgeLength = std::abs(y0 - y1);  // 确定正方形的边长
            if (edgeLength == 0) {
                continue;  // 如果是同一个点，则跳过
            }

            const int leftPointPairNums = cntY[y0][x0 - edgeLength] * cntY[y1][x0 - edgeLength];   // 左边的符合要求的点对数
            const int rightPointPairNums = cntY[y0][x0 + edgeLength] * cntY[y1][x0 + edgeLength];  // 右边的符合要求的点对数
            ans += x1y1PointNums * (leftPointPairNums + rightPointPairNums);
        }
        return ans;
    }
};

/**
 * Your DetectSquares object will be instantiated and called as such:
 * DetectSquares* obj = new DetectSquares();
 * obj->add(point);
 * int param_2 = obj->count(point);
 */