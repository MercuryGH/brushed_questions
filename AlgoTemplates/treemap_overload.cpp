#include <memory>
#include <map>
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
    friend std::ostream &operator<<(std::ostream &out, const Key &k) {
        out << k.first << ", " << k.second << ", " << k.third;
        return out;
    }
};

int main()
{
    const auto cmp = [](const Key &k1, const Key &k2) {
        return k1.first < k2.first;
    };
    std::map<Key, int, decltype(cmp)> keyMap(cmp);

    Key k("123", "456", 100);
    keyMap[k] = 1;
    Key k2("100", "333", 3);
    keyMap[k2] = 2;

    for (const auto [k, v] : keyMap) {
        std::cout << k << " " << v << "\n";
    }

    return 0;
}