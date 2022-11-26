# BOJ 11402 이항 계수 4

import sys
input = sys.stdin.readline


def combination(n, k, mod):
    if n < k:
        return 0

    k = min(k, n - k)
    num = den = 1
    for i in range(k):
        num = num * (n - i) % mod
        den = den * (i + 1) % mod
    
    return num * pow(den, mod - 2) % mod


def lucas(n, k, mod):
    k = min(k, n - k)
    ret = 1
    while k:
        ret = ret * combination(n % mod, k % mod, mod) % mod
        n //= mod
        k //= mod

    return ret


n, k, p = map(int, input().split())
print(lucas(n, k, p))
