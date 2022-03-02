import math
from math import comb

s = '12345'

s1 = s[: -1]
s2 = s[-1]
s3 = s[-2 : : -1]
s4 = s[: -1][:: -1]
lamb = lambda x: x + 1
a = [-2, -1, 0]
res = min(a, key=lambda x: abs(x - 1))

print(res)