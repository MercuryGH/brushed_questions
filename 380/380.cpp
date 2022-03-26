#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cassert>
using std::vector, std::string;

/**
 * 实现RandomizedSet 类：
    RandomizedSet() 初始化 RandomizedSet 对象
    bool insert(int val) 当元素 val 不存在时，向集合中插入该项，并返回 true ；否则，返回 false 。
    bool remove(int val) 当元素 val 存在时，从集合中移除该项，并返回 true ；否则，返回 false 。
    int getRandom() 随机返回现有集合中的一项（测试用例保证调用此方法时集合中至少存在一个元素）。每个元素应该有 相同的概率 被返回。
    你必须实现类的所有函数，并满足每个函数的 平均 时间复杂度为 O(1) 。

    思路：
    * 动态数组存储元素值
    * 哈希表存储存储 值 到 所在的数组下标 的映射。
 */
class RandomizedSet
{
    vector<int> elements;
    std::unordered_map<int, int> elementIndex;

public:
    RandomizedSet()
    {
    }

    bool insert(int val)
    {
        if (elementIndex.find(val) == elementIndex.end())
        {
            elements.push_back(val);
            elementIndex[val] = elements.size() - 1;
            return true;
        }
        return false;
    }

    bool remove(int val)
    {
        if (elementIndex.find(val) != elementIndex.end())
        {
            const int index = elementIndex[val]; // 取出值所在的数组下标
            std::swap(elements[index], elements[elements.size() - 1]); // 将数组中的该值与数组末尾元素交换
            elementIndex[elements[index]] = index; // 数组末尾的那个元素获取新的下标

            elementIndex.erase(val); // 删掉数组末尾的元素
            elements.pop_back(); // 删掉数组末尾的元素
            return true;
        }
        return false;
    }

    int getRandom()
    {
        assert(elements.size() > 0);
        return elements[std::rand() % (elements.size())];
    }
};
