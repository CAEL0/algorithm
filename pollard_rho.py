# BOJ 4149 큰 수 소인수분해

import sys
from random import randint
from math import gcd
sys.setrecursionlimit(10 ** 5)
input = sys.stdin.readline


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
        return ()

    if x % 2 == 0:
        return 2, *pollard_rho(x // 2)

    if miller_rabin(x):
        return x,

    while True:
        c = randint(1, n - 1)
        flag = True
        t = r = 1
        g = 1
        while g == 1:
            t = (t ** 2 + c) % x
            r = (r ** 4 + 2 * c * r ** 2 + c ** 2 + c) % x
            g = gcd(abs(t - r), x)
            if g == n:
                flag = False
                break

        if flag:
            return *pollard_rho(g), *pollard_rho(x // g)


n = int(input())
ans = pollard_rho(n)
for p in sorted(ans):
    print(p)
