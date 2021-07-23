"""
The Miller–Rabin primality test or Rabin–Miller primality test is a probabilistic primality test: an algorithm 
which determines whether a given number is likely to be prime, similar to the Fermat primality test and the 
Solovay–Strassen primality test.
if n < 2,047, it is enough to test a = 2;
if n < 1,373,653, it is enough to test a = 2 and 3;
if n < 9,080,191, it is enough to test a = 31 and 73;
if n < 25,326,001, it is enough to test a = 2, 3, and 5;
if n < 3,215,031,751, it is enough to test a = 2, 3, 5, and 7;
if n < 4,759,123,141, it is enough to test a = 2, 7, and 61;
if n < 1,122,004,669,633, it is enough to test a = 2, 13, 23, and 1662803;
if n < 2,152,302,898,747, it is enough to test a = 2, 3, 5, 7, and 11;
if n < 3,474,749,660,383, it is enough to test a = 2, 3, 5, 7, 11, and 13;
if n < 341,550,071,728,321, it is enough to test a = 2, 3, 5, 7, 11, 13, and 17.
"""

from math import log2


def power(num, exp, mod):
    if exp == 0:
        return 1

    num %= mod
    arr = [num]
    for _ in range(int(log2(exp))):
        arr.append(pow(arr[-1], 2, mod))

    res = 1
    bin_exp = bin(exp)[2:]
    for j in range(len(bin_exp)):
        if bin_exp[- j - 1] == '1':
            res = res * arr[j] % mod

    return res


def miller_rabin(x):
    if x == 1:
        return False

    s = 0
    d = x - 1
    while d % 2 == 0:
        s += 1
        d //= 2

    for a in [2, 7, 61]:
        if a >= x - 1:
            break

        b = power(a, d, x)
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
