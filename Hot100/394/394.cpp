#include <string>
using std::string;

/**
 * 递归模拟题
 * 细节很多，一次性难以写对
 */
class Solution {
    string getString(const string s, int &sIndex) {
        const int len = s.size();

        string res;
        int repeatCnt = 0; // 读到的重复数，如 3[aa] 中的 3
        for (int i = sIndex; i < len; i++) {
            const char curChar = s[i];

            if (isdigit(curChar)) { // 十进制解析重复数
                repeatCnt *= 10;
                repeatCnt += curChar - '0';
            } else if (curChar == '[') { // 开始递归
                i++; // 进入待解析的部分
                string parsedStr = getString(s, i);
                while (repeatCnt--) { // 让 res += (parsedStr * repeatCnt)
                    res += parsedStr;
                }
                repeatCnt = 0;
            } else if (curChar == ']') {
                sIndex = i; // 更新全局字符串 s 的下标（可以看作是 getString() 的第二个返回值）
                return res;
            } else {
                res += curChar;
            }
        }
        return res;
    }
public:
    string decodeString(string s) {
        int sIndex = 0;
        return getString(s, sIndex);
    }
};