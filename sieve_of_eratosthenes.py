"""
In mathematics, the sieve of Eratosthenes is an ancient algorithm for finding all prime numbers up to any given limit.
"""

# BOJ 1978 소수 찾기

import sys

n = int(sys.stdin.readline())
check = [0] * (n + 1)
sieve = [1] * (n + 1)
sieve[0] = sieve[1] = 0

for i in range(2, len(sieve)):
    if sieve[i]:
        check[i] = i
        for j in range(i * i, len(sieve), i):
            if sieve[j]:
                check[j] = i
            sieve[j] = 0


def factorization(x):
    res = []
    idx = check[x]
    while x > 1:
        while x % idx == 0:
            res.append(idx)
            x //= idx
        idx = check[x]

    if x > 1:
        res.append(x)
    return res


def isprime(x):
    if x == 2:
        return True

    if (x < 2) or (x % 2 == 0):
        return False

    for p in range(3, int(x ** 0.5) + 1):
        if x % p == 0:
            return False
    return True
