"""
In mathematics, the sieve of Eratosthenes is an ancient algorithm for finding all prime numbers up to any given limit.
"""

n = 5000001
check = [0] * (n + 1)
sieve = [1] * (n + 1)
sieve[0] = 0
sieve[1] = 0

for i in range(2, n + 1):
    if sieve[i]:
        check[i] = i
        for j in range(2, (n // i + 1)):
            if sieve[j * i]:
                check[j * i] = i
            sieve[j * i] = 0


def factorization(x):
    res = []
    idx = check[x]
    while x > 1:
        while x % idx == 0:
            res.append(idx)
            x //= idx

        idx = check[x]
        if sieve[idx] == 0:
            continue

    if x > 1:
        res.append(x)
    
    return res
