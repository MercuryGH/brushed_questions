#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::vector, std::string;

struct A {
    vector<int> v;
    A() {
    }

    void addElement(int e) {
        v.push_back(e);
    }

    vector<int> getVector() const {
        return std::move(v);
    }
};

int main()
{
    A a;
    a.addElement(1);
    a.addElement(2);
}