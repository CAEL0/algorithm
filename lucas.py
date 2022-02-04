"""
In number theory, Lucas's theorem expresses the remainder of division of the binomial coefficient mCn
by a prime number p in terms of the base p expansions of the integers m and n.
Lucas's theorem first appeared in 1878 in papers by Édouard Lucas.
"""


def extended_gcd(a, b):
    x0, x1, y0, y1 = 1, 0, 0, 1
    while b != 0:
        z, a, b = a // b, b, a % b
        x0, x1 = x1, x0 - z * x1
        y0, y1 = y1, y0 - z * y1
    return x0, y0


def combination(a, b, p):
    if a < b:
        return 0

    b = min(b, a - b)
    num = 1
    den = 1
    for i in range(b):
        num = (num * (a - i)) % p
        den = (den * (i + 1)) % p

    x, y = extended_gcd(den, p)
    return (num * x) % p


def lucas(n, k, p):
    k = min(k, n - k)
    num = []
    den = []
    while n:
        num.append(n % p)
        n //= p

    while k:
        den.append(k % p)
        k //= p

    res = 1
    for i in range(len(den)):
        res = (res * combination(num[i], den[i], p)) % p
    return res
