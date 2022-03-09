#include <algorithm>
#include <ctime>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <list>
#include <string>
using std::vector, std::string;

class Solution
{
public:
    string longestCommonPrefix(vector<string> &strs)
    {
        int ans = 0;
        for (int i = 0; ; i++)
        {
            const string &curStr = strs[0];
            if (curStr.length() <= i) {
                break;
            }

            const char curChar = curStr[i];
            for (const auto &str : strs)
            {
                if (str.length() <= i || str[i] != curChar) {
                    goto END;
                }
            }
            ans++;
        }
        END:
        string str = strs[0];
        str.resize(ans);
        return str;
    }
};

int main()
{
    vector<int> v = {1, 2, 3, 4, 5};
    int i = 1;
    std::move(v.begin() + i, v.end(), v.begin());

    for (const int num : v) {
        std::cout << num << "\n";
    }

    return 0;
}