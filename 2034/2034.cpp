#include <map>
#include <set>  
#include <algorithm>

/** 
 * 其实是一道很简单的HashTable模拟维护题
 * Java的TreeMap会很方便
 */
class StockPrice {
    int latestTime;
    std::map<int, int> timePriceHash;
    std::multiset<int> prices;  // multiset是允许元素重复的**有序**集合
public:
    StockPrice() {
        this->latestTime = 0;
    }
    
    void update(int timestamp, int price) {
        this->latestTime = std::max(this->latestTime, timestamp);
        auto itr = this->timePriceHash.find(timestamp);
        if (itr != this->timePriceHash.end()) {
            this->prices.erase(
                this->prices.find(
                    itr->second
                )
            );
        }
        this->prices.insert(price);
        this->timePriceHash[timestamp] = price;
    }
    
    int current() {
        return this->timePriceHash[this->latestTime];
    }
    
    int maximum() {
        return *(this->prices.rbegin());  // rbegin 在有序数据结构中相当于 end - 1，但在非有序数据结构中不一定
    }
    
    int minimum() {
        return *(this->prices.begin());
    }
};

/**
 * Your StockPrice object will be instantiated and called as such:
 * StockPrice* obj = new StockPrice();
 * obj->update(timestamp,price);
 * int param_2 = obj->current();
 * int param_3 = obj->maximum();
 * int param_4 = obj->minimum();
 */