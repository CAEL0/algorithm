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


def factorization(k):
    factor = defaultdict(int)
    idx = 1
    m = k ** 0.5
    while (k > 1) and (idx < m):
        idx += 1
        if sieve[idx] == 0:
            continue

        while k % idx == 0:
            factor[idx] += 1
            k //= idx

    if k > 1:
        factor[k] += 1

    return factor
