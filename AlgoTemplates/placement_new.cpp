#include <memory>
#include <vector>
#include <iostream>
using std::vector;

class A
{
private:
    int data;

public:
    A(int indata)
        : data(indata) {}
    void print()
    {
        std::cout << data << "\n";
    }
};
int main()
{
    const int size = 10;
    char buf[size * sizeof(A)]; // 内存分配
    for (size_t i = 0; i < size; i++)
    {
        new (buf + i * sizeof(A)) A(i); // 对象构造
    }
    A *arr = (A *)buf;
    for (size_t i = 0; i < size; i++)
    {
        arr[i].print();
        arr[i].~A(); // 对象析构
    }
    // 栈上预分配的内存自动释放
    return 0;
}