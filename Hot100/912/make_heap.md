# `std::make_heap`的用法

在一些场合，往优先队列里添加$n$个元素这种初始化的方式不够优雅。因此，`std::make_heap`及其帮手可能可以给我们提供一些帮助。

## 线性建堆

```cpp
std::vector<int> nums = {15, 9, 7, 8, 20, -1, 7, 4};
std::make_heap(nums.begin(), nums.end());

for (const int num : nums) {
    std::cout << num << " ";
}
```

输出结果为 `20 15 7 8 9 -1 7 4`，可见是大顶堆。如果希望建立小顶堆，使用 `std::make_heap(nums.begin(), nums.end(), std::greater<int>());`即可。

## 往堆里添加元素（insert）

必须严格按照以下步骤进行：

1. 首先，`nums.push_back(element)`
2. 然后，`std::push_heap(nums.begin(), nums.end())`。如果是小顶堆，使用 `std::push_heap(nums.begin(), nums.end(), std::greater<int>())`

所以，建完堆以后，确实不如优先队列好用了。

## 删除堆顶元素（delete_top）

必须严格按照以下步骤进行：

* 首先，`std::pop_heap(nums.begin(), nums.end())`。如果是小顶堆，也要加上 `std::greater<int>()`。
* 然后，`nums.pop_back()`

## 获取堆顶元素

`nums[0]`即可。
