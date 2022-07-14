# construct table

import sys
input = sys.stdin.readline

n = int(input())
phi = [i for i in range(n + 1)]
for i in range(2, n + 1):
    if phi[i] == i:
        for j in range(i, n + 1, i):
            phi[j] = phi[j] * (i - 1) // i


# euler phi function

def phi(x):
    res = x
    for i in range(2, int(x ** 0.5) + 2):
        if x % i == 0:
            res = res * (i - 1) // i
            while x % i == 0:
                x //= i
    
    if x > 1:
        res = res * (x - 1) // x
    return res
