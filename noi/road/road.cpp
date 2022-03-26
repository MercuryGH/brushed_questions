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
    int n;
    std::cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    int ans = a[1];
    for (int i = 2; i <= n; i++)
    {
        if (a[i] > a[i - 1])
        {
            ans += (a[i] - a[i - 1]);
        }
    }

    std::cout << ans << "\n";
    return 0;
}