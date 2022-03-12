#include <algorithm>
#include <vector>
#include <string>
using std::vector, std::string;

/**
 * 整数翻转
 * STL std::stoi 会抛出 std::out_of_range 异常，捕获之即可
 */
class Solution {
public:
    int reverse(int x) {
        string str = std::to_string(x);
        const bool sign = (x < 0);
        std::reverse(str.begin(), str.end());

        if (sign == true) {
            str = '-' + str;
        }

        int ret = 0;
        try {
            ret = std::stoi(str);
        } catch (const std::out_of_range &oor) {
            return 0;
        } 
        return ret;
    }
};