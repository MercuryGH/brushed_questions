#include <memory>
#include <vector>
#include <iostream>
#include <string>
using std::vector, std::string;

class Type
{
public:
    int a = 1;
};

template <typename T>
class unique_ptr
{
public:
    unique_ptr() : m_ptr(nullptr) {}
    unique_ptr(T *ptr) : m_ptr(ptr) {}
    ~unique_ptr()
    {
        delete m_ptr;
    }
    T &operator*() const { return *m_ptr; }
    T *operator->() const { return m_ptr; }
    operator bool() const { return m_ptr != nullptr; } // 提供到 bool 类型的隐式转换

    // 移动构造
    unique_ptr(unique_ptr &&rhs) noexcept // 自己实现的移动构造必须 noexcept，否则编译器可能不会把拷贝构造优化成移动构造
    // 最佳实践：只在移动构造和移动赋值必须用 noexcept，其他地方一般不需要加 noexcept 优化
    {
        m_ptr = rhs.m_ptr;
        rhs.m_ptr = nullptr;
    }
    // 移动赋值
    unique_ptr &operator=(unique_ptr &&rhs) noexcept // 同上
    {
        m_ptr = rhs.m_ptr;
        rhs.m_ptr = nullptr;
        return *this;
    }
    // 根据C++的规则，我们提供了移动构造而没有提供拷贝构造，那拷贝构造就自动被禁用。但还是推荐显式禁用
    unique_ptr(const unique_ptr &rhs) = delete;
    unique_ptr &operator=(const unique_ptr &rhs) = delete;

private:
    T *m_ptr;
};

template <typename T>
class shared_count;

template <typename T>
class shared_ptr
{
public:
    shared_ptr() : m_ptr(nullptr) {}
    shared_ptr(T *ptr) : m_ptr(ptr)
    {
        if (ptr)
        {
            m_shared_count = new shared_count<T>();
        }
    }
    ~shared_ptr()
    {
        if (m_ptr)
        {
            m_shared_count->reduce_count();
            if (m_shared_count->get_count() == 0)
            {
                delete m_ptr;
                delete m_shared_count;
                std::cout << "~smart_ptr\n";
            }
        }
    }
    T &operator*() const { return *m_ptr; }
    T *operator->() const { return m_ptr; }
    operator bool() const { return m_ptr != nullptr; }

    shared_ptr(const shared_ptr &rhs)
    {
        m_ptr = rhs.m_ptr;
        m_shared_count = rhs.m_shared_count;
        m_shared_count->add_count();
    }
    shared_ptr &operator=(const shared_ptr &rhs)
    {
        m_ptr = rhs.m_ptr;
        m_shared_count = rhs.m_shared_count;
        m_shared_count->add_count();
        return *this;
    }
    shared_ptr(shared_ptr &&rhs) noexcept
    {
        m_ptr = rhs.m_ptr;
        rhs.m_ptr = nullptr;
    }
    // 移动赋值
    shared_ptr &operator=(shared_ptr &&rhs) noexcept 
    {
        m_ptr = rhs.m_ptr;
        rhs.m_ptr = nullptr;
        return *this;
    }
    int use_count() const
    {
        if (m_ptr)
        {
            return m_shared_count->get_count();
        }
        return 0;
    }

private:
    T *m_ptr;
    shared_count<T> *m_shared_count;
};

template<typename T>
class shared_count
{
private:
    friend class shared_ptr<T>;
    shared_count() : cnt(1) {}
    void add_count()
    {
        cnt++;
    }
    void reduce_count()
    {
        cnt--;
    }
    int get_count() const
    {
        return cnt;
    }

    int cnt;
};

int main(int argc, char const *argv[])
{
    // std::shared_ptr<Test> t = std::make_shared<Test>(3);
    // int n = t.operator->()->n; // 重载 -> 运算符：语句 p->m 会被解释为 (p.operator->())->m
    // std::cout << n << "\n";
    unique_ptr<Type> myPtr(new Type());
    std::cout << myPtr->a << "\n";
    string s;
    std::cout << s << "\n";
    
    // auto thisPtr = myPtr;

    shared_ptr<Type> mySPtr(new Type());
    std::cout << mySPtr->a << "\n";

    return 0;
}