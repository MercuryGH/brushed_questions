#include <algorithm>
#include <random>
#include <cstdlib>
#include <cmath>
#include <vector>
using std::vector;

class Solution {
public:
    double x, y, r;
    static constexpr double PI() { return std::acos(-1); }
    mutable std::mt19937 re;

    Solution(double radius, double x_center, double y_center)
        : x(x_center), y(y_center), r(radius), re(std::random_device{}()) {}
    
    vector<double> randPoint() const {
        std::uniform_real_distribution<double> udr(0, r * r), udt(0, 2 * PI());
        const auto ur = sqrt(udr(re)), ut = udt(re);
        return {x + ur * cos(ut), y + ur * sin(ut)};
    }
};
