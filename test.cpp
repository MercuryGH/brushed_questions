#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <array>

class Base
{
private:
    /* data */
public:
    virtual void f() {}
    Base(/* args */);
    ~Base();
};

Base::Base(/* args */)
{
    std::cout << "Base\n";
}

Base::~Base()
{
    std::cout << "Delete Base\n";
}

class Derived: public Base
{
private:
    /* data */
public:
    void f() override {}
    Derived(/* args */);
    ~Derived();
};

Derived::Derived(/* args */)
{
    std::cout << "Derived\n";
}

Derived::~Derived()
{
    std::cout << "Delete Derived\n";
}


int main(void) {
    // Derived derived;
    Base *b = new Derived();
    delete b;

    return 0;
}