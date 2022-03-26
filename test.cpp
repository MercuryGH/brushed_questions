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
using std::vector, std::string;

int main()
{
    bool b = false;
    vector<bool> vs = {b, b, b, b, b, b};
    vector<int> vv = {b, b, b, b, b, b};
    std::cout << sizeof(vs) << " " << sizeof(vv) << "\n";

    return 0;
}