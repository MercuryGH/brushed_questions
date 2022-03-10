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

// using KeyType = int;
// using ValueType = int;

template<typename KeyType=int, typename ValueType=int>
class LRUCache
{
    int capacity;
    int curSize;
    std::list<std::pair<KeyType, ValueType>> cache; // 相当于 ListNode
    std::unordered_map<
        KeyType,
        std::list<std::pair<KeyType, ValueType>>::iterator // value 相当于 ListNode *
    > lru;

public:
    LRUCache(int capacity) : capacity(capacity), curSize(0)
    {
    }

    ValueType get(KeyType key)
    {
        if (lru.find(key) == lru.end())
        {
            return -1;
        }
        const auto nodeItr = lru[key];
        const auto node = *nodeItr;
        cache.erase(nodeItr);
        cache.push_front(node); // 如果写成 *nodeItr 就会有BUG，因为已经被 erase 了！！
        lru[key] = cache.begin();
        return node.second;
    }

    void put(KeyType key, ValueType value)
    {
        const auto newNode = std::make_pair(key, value);
        if (lru.find(key) != lru.end())
        { // 更新
            cache.erase(lru[key]);
            curSize--;
        }
        else
        { // 添加
            // < C++11，std::list 获取size() 的时间复杂度可能是 O(n) 的
            // 但 C++11 必须是 O(1) 的
            // 所以其实这里用 curSize 可能效率反而低
            if (capacity == curSize)
            { // 满了，要淘汰末尾的
                lru.erase(cache.back().first);
                cache.pop_back();
                curSize--;
            }
        }
        // 加新的
        cache.push_front(newNode);
        lru[key] = cache.begin();
        curSize++;
    }
};

int main(int argc, char const *argv[])
{
    LRUCache<int, int> lru(2);
    return 0;
}
