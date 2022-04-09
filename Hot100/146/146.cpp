#include <unordered_map>

class SelfImplLRUCache {
    using KeyType = int;
    using ValueType = int;

    struct Entry {
        Entry *prev;
        Entry *next;
        KeyType key;
        ValueType value;
        Entry(KeyType k, ValueType v): key(k), value(v), prev(nullptr), next(nullptr) {} 
        Entry(): key(0), value(0), prev(nullptr), next(nullptr) {}
    };

    std::unordered_map<KeyType, Entry *> lru;
    int capacity;
    int curSize;
    Entry *const dummyHead = new Entry();
    Entry *const dummyTail = new Entry();

public:
    SelfImplLRUCache(int capacity): capacity(capacity), curSize(0) {
        dummyHead->next = dummyTail;
        dummyTail->prev = dummyHead;
    }

    ValueType get(KeyType key) {
        if (lru.find(key) == lru.end()) {
            return -1;
        }

        Entry *ptrEntry = lru.at(key);
        Entry entry = *ptrEntry;
        erase(ptrEntry);
        insert_front(entry);
        lru[key] = dummyHead->next;

        return entry.value;
    }

    void put(KeyType key, ValueType value) {
        if (lru.find(key) == lru.end()) {
            if (curSize >= capacity) {
                lru.erase(dummyTail->prev->key);
                erase_back();
            } else {
                curSize++;
            }
            insert_front(Entry(key, value));
        } else {
            Entry *ptrEntry = lru.at(key);
            Entry entry = *ptrEntry;
            entry.value = value;
            erase(ptrEntry);
            insert_front(entry);
        }
        lru[key] = dummyHead->next;
    }
private:
    void erase(Entry *entry) { // 给定指针删除
        entry->prev->next = entry->next;
        entry->next->prev = entry->prev;
        delete entry;
    }
    void insert_front(const Entry &entry) { // 在最前面插入
        Entry *newEntry = new Entry(entry.key, entry.value);
        dummyHead->next->prev = newEntry;

        newEntry->next = dummyHead->next;
        newEntry->prev = dummyHead;
        dummyHead->next = newEntry;
    }
    void erase_back() { // 在最后面删除
        Entry *toBeDeleted = dummyTail->prev;
        erase(toBeDeleted);
    }
};

// std::list + 模板实现方式
// 需要使用 LRUCache<> 来实例化一个默认参数为 <int, int> 的模板对象

// 把这个放到 LRUCache 类里面也行。这样每实例化一个LRUCache 对象，也会为这个对象实例化一个 KvPair（编译期就能确定实例化的类型）
template <typename KeyType, typename ValueType>
struct KvPair
{
    KvPair(KeyType k, ValueType v) : key(k), value(v) {}
    KeyType key;
    ValueType value;
};

template <typename KeyType = int, typename ValueType = int>
class LRUCache
{
    // template <typename KeyType=int, typename ValueType=int>
    std::list<KvPair<KeyType, ValueType>> container;
    // typename 是为了让编译器知道后面这个是一个类型的名称
    std::unordered_map<KeyType, typename std::list<KvPair<KeyType, ValueType>>::iterator> lru;
    int capacity;

public:
    LRUCache(int capacity) : capacity(capacity) {}

    ValueType get(KeyType key)
    {
        if (lru.find(key) == lru.end())
        { // 找不到
            return -1;
        }

        // 找得到
        auto getKvPairItr = lru.at(key);
        KvPair<KeyType, ValueType> getKvPair = *getKvPairItr;
        container.erase(getKvPairItr);

        container.push_front(getKvPair);
        lru[key] = container.begin();

        return getKvPair.value;
    }

    void put(KeyType key, ValueType value)
    {
        if (lru.find(key) == lru.end())
        {
            if (container.size() >= capacity)
            {
                lru.erase(container.back().key);
                container.pop_back();
            }
            container.emplace_front(key, value);
        }
        else
        {
            auto getKvPairItr = lru.at(key);
            KvPair<KeyType, ValueType> getKvPair = *getKvPairItr;
            getKvPair.value = value;

            container.erase(getKvPairItr);
            container.push_front(getKvPair);
        }
        lru[key] = container.begin();
    }
};