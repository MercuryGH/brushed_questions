import math
from math import comb

m = 100

f = [0]
for i in range(1, m + 1):
    p_i = pow((2 / 3), i)

    prev_sum = 0
    for j in range(0, i):
        p_j = comb(i, j) * pow((2 / 3), j) * pow((1 / 3), i - j)
        prev_sum += p_j * f[j]
    f.append((1 + prev_sum) / (1 - p_i))

for f_i in f:
    print(f_i) 