#include <memory>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>
using std::vector, std::string;

struct Key
{
    string first;
    string second;
    int third;
    Key(string f, string s, int t): first(f), second(s), third(t) {}

    bool operator==(const Key &other) const
    {
        return (first == other.first && second == other.second && third == other.third);
    }
};

template <>
struct std::hash<Key>
{
    std::size_t operator()(const Key &k) const
    {
        using std::hash;
        return ((hash<string>()(k.first) ^ (hash<string>()(k.second) << 1)) >> 1) ^ (hash<int>()(k.third) << 1);
    }
};

int main()
{
    std::unordered_map<Key, int> keyMap;
    Key k("12234", "afsf", 30);
    keyMap[k] = 3;

    string tmp = "122";
    tmp += "34";
    Key k2(tmp, "afsf", 10 + 20);
    std::cout << keyMap[k2] << "\n";

    return 0;
}