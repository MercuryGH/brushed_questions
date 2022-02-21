#include <string>

/**
 * 要求：找出最长的包含同一字母的大小写的子串。
 * 暴力做法（枚举所有子串）需要 O(n^3) 复杂度
 * 分治做法如下：
 * 时间复杂度 T(n) = 2T(n / 2) + O(n ^ 2)，T(n) = O(n ^ 2)
 * 其实还可以用前缀和优化，不会
 */
class Solution {
    inline static char toUpperCase(const char c) {
        return c - 32;
    }
    inline static char toLowerCase(const char c) {
        return c + 32;
    }
    inline static bool isUpperCase(const char c) {
        return c >= 'A' && c <= 'Z';
    }
    inline static bool isLowerCase(const char c) {
        return c >= 'a' && c <= 'z';
    }
    inline static bool containsChar(const std::string &s, const char c) {
        for (const char ch : s) {
            if (c == ch) {
                return true;
            }
        }
        return false;
    }
    inline static bool isIsolated(const std::string &s, const char c) {
        return (isUpperCase(c) == true && containsChar(s, toLowerCase(c)) == false)
            || (isLowerCase(c) == true && containsChar(s, toUpperCase(c)) == false);
    }
public:
    std::string longestNiceSubstring(const std::string s) {
        const int n = s.length();
        if (n < 2) {
            return "";
        }
        for (int i = 0; i < n; i++) {
            const char c = s[i];
            // 如果 s 中的字母 c 是孤独的，就排除在外，然后对两边分治处理
            // 注意：分治点可能并不唯一，选最小的那个即可
            if (isIsolated(s, c)) {   // 注意：isIsolated 的时间复杂度是 O(n)
                // const std::string lString = std::string(s.begin(), s.begin() + i);
                // const std::string rString = std::string(s.begin() + i + 1, s.end());
                const std::string lRes = longestNiceSubstring(s.substr(0, i));
                const std::string rRes = longestNiceSubstring(s.substr(i + 1));
                return (lRes.length() >= rRes.length()) ? lRes : rRes;
            }
        }
        return s;  // 不存在分治点——原字符串就是美好的
    }
};
