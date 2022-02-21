#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>

/**
 * 字母异位词分组
 * 将排序结果作为哈希表的 key，很巧妙的解法
 */
class Solution
{
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string> &strs)
    {
        std::unordered_map<std::string, std::vector<std::string>> mp;
        for (const std::string &str : strs) {
            std::string key = str;
            std::sort(key.begin(), key.end());
            mp[key].emplace_back(str);
        }
        std::vector<std::vector<std::string>> ans;
        for (const auto [k, v] : mp) {
            ans.emplace_back(v);
        }
        return ans;
    }
};