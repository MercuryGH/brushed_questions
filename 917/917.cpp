#include <string>
using std::string;

/**
 * 别老想着std::reverse()了，STL废物
 */
class Solution {
public:
    string reverseOnlyLetters(string s) {
        const int n = s.size();

        int l = 0;
        int r = n - 1;
        while (true) {
            while (l < r && !isalpha(s[l])) { // 判断左边是否扫描到字母
                l++;
            }
            while (r > l && !isalpha(s[r])) { // 判断右边是否扫描到字母
                r--;
            }
            if (l >= r) {
                break;
            }
            std::swap(s[l], s[r]);
            l++;
            r--;
        }
        return s;
    }
};