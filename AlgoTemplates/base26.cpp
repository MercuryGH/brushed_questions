// 10进制与26进制互相转换
// 可能存在缺陷
// 要点：转10进制就是累加power，转26进制就是求对数后填充

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

const char CHAR_TABLE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
#define BASE 26

int s26toi10(char *s)
{
    int ret = 0;
    int curIndex = strlen(s);
    int len = curIndex;
    for (int i = 0; i < len; i++)
    {
        int curVal = s[i] - 'A';
        ret += curVal * (int)pow(BASE, --curIndex);
    }
    return ret;
}

char *i10tos26(int num)
{
    int l = num, i = 0;
    while (true)
    {
        l /= BASE;
        i++;
        if (l == 0)
        {
            break;
        }
    } // l = BASE ** i ( log )

    char *ret = (char *)malloc(i + 1);
    ret[i] = 0;

    l = num;
    while (true)
    {
        int index = l % BASE;
        l /= BASE;
        ret[--i] = CHAR_TABLE[index];
        if (l == 0)
        {
            break;
        }
    }
    return ret;
}

bool isNum(char *s)
{
    return s[0] >= '0' && s[0] <= '9';
}