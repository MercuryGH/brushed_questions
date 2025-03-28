#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

bool isprime(int a)
{
    if (a <= 1) return 0;
    for (int i = 2; i <= sqrt(a); i++)
    {
        if (a % i == 0) return 0;
    }
    return 1;
}

int main(void)
{
    int n;
    cin >> n;
    cout << isprime(n);
    return 0;
}