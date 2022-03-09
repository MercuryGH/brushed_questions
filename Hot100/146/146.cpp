#include <unordered_map>

class SelfImplLRUCache {
    struct LinkedNode {
        int key, value;
        LinkedNode *prev, *next;
        LinkedNode(): key(0), value(0), prev(nullptr), next(nullptr) {}
        LinkedNode(int k, int v): key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    std::unordered_map<int, LinkedNode *> lru;
    LinkedNode *dummyHead; // 越靠近头，越频繁使用
    LinkedNode *dummyTail; // 越靠近尾，越不频繁使用
    int curSize;
    int capacity;

    void addMru(LinkedNode *node) {
        node->prev = dummyHead;
        node->next = dummyHead->next;
        dummyHead->next->prev = node;
        dummyHead->next = node;
    }
    void updateMru(LinkedNode *node) {
        this->removeNode(node);
        this->addMru(node);
    }
    void removeNode(LinkedNode *node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    LinkedNode *removeLru() {
        LinkedNode *tailNode = dummyTail->prev;
        this->removeNode(tailNode);
        return tailNode;
    }
    void checkSizeOverflow() {
        if (this->curSize > this->capacity) {
            LinkedNode *removed = this->removeLru();
            lru.erase(removed->key);
            delete removed;
            this->curSize--;
        }
    }

public:
    SelfImplLRUCache(int capacity): capacity(capacity), curSize(0) {
        this->dummyHead = new LinkedNode();
        this->dummyTail = new LinkedNode();
        dummyHead->next = dummyTail;
        dummyTail->prev = dummyHead;
    }
    
    int get(int key) {
        if (lru.find(key) == lru.end()) {
            return -1;
        }
        LinkedNode *node = lru[key];
        this->updateMru(node);
        return node->value;
    }
    
    void put(int key, int value) {
        if (lru.find(key) == lru.end()) {
            LinkedNode *node = new LinkedNode(key, value);
            lru[key] = node;
            this->addMru(node);
            this->curSize++;
            this->checkSizeOverflow();
        } else {
            LinkedNode *node = lru[key];
            node->value = value;
            this->updateMru(node);
        }
    }
};

using KeyType = int;
using ValueType = int;

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