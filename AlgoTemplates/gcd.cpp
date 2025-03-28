#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int gcd(int x, int y)
{
	return y == 0 ? x : gcd(y, x % y);
}

int main(void)
{
	return 0;
}