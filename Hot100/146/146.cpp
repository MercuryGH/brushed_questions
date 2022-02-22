#include <unordered_map>

class LRUCache {
    struct LinkedNode {
        int key, value;
        LinkedNode *prev, *next;
        LinkedNode(): key(0), value(0), prev(nullptr), next(nullptr) {}
        LinkedNode(int k, int v): key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    std::unordered_map<int, LinkedNode *> lru;
    LinkedNode *dummyHead;
    LinkedNode *dummyTail;
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
    LRUCache(int capacity): capacity(capacity), curSize(0) {
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

