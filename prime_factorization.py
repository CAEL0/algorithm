from collections import defaultdict

n = int(input())
m = int(n ** 0.5)
sieve = [1] * (m + 1)
sieve[0] = 0
sieve[1] = 0

for i in range(2, int((m + 1) ** 0.5) + 1):
    if sieve[i]:
        for j in range(2, (m // i + 1)):
            sieve[j * i] = 0


def factorization(x):
    factor = defaultdict(int)
    idx = 1
    m = x ** 0.5
    while (x > 1) and (idx < m):
        idx += 1
        if sieve[idx]:
            while x % idx == 0:
                factor[idx] += 1
                x //= idx

    if x > 1:
        factor[x] += 1

    return factor


def isprime(x):
    if x == 2:
        return True

    if (x < 2) or (x % 2 == 0):
        return False

    for p in range(3, int(x ** 0.5) + 1):
        if x % p == 0:
            return False
    return True

