"""
Pollard's rho algorithm is an algorithm for integer factorization. It was invented by John Pollard in 1975.
It uses only a small amount of space, and its expected running time is proportional to the square root of
the size of the smallest prime factor of the composite number being factorized.
"""

# BOJ 4149 큰 수 소인수분해

import sys
from random import randint
from math import gcd
sys.setrecursionlimit(10 ** 5)


def miller_rabin(x):
    if x == 1:
        return False

    s = 0
    d = x - 1
    while d % 2 == 0:
        s += 1
        d //= 2

    for a in [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]:
        if a >= x - 1:
            break

        b = pow(a, d, x)
        if b in [1, x - 1]:
            continue

        if s == 1:
            return False

        for _ in range(s - 1):
            b = pow(b, 2, x)
            if b == x - 1:
                break
        else:
            return False
    return True


def pollard_rho(x):
    if x == 1:
        return

    if x % 2 == 0:
        ans.append(2)
        pollard_rho(x // 2)
        return

    if miller_rabin(x):
        ans.append(x)
        return

    while True:
        c = randint(1, x - 1)
        flag = True
        t = r = g = 1
        while g == 1:
            t = (t ** 2 + c) % x
            r = (r ** 4 + 2 * c * r ** 2 + c ** 2 + c) % x
            g = gcd(abs(t - r), x)
            if g == x:
                flag = False
                break

        if flag:
            pollard_rho(g)
            pollard_rho(x // g)
            return


x = int(sys.stdin.readline())
ans = []
pollard_rho(x)
