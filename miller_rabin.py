"""
The Miller–Rabin primality test or Rabin–Miller primality test is a probabilistic primality test:
an algorithm which determines whether a given number is likely to be prime,
similar to the Fermat primality test and the Solovay–Strassen primality test.
if n < 2,047, it is enough to test a = 2;
if n < 1,373,653, it is enough to test a = 2 and 3;
if n < 9,080,191, it is enough to test a = 31 and 73;
if n < 25,326,001, it is enough to test a = 2, 3, and 5;
if n < 3,215,031,751, it is enough to test a = 2, 3, 5, and 7;
if n < 4,759,123,141, it is enough to test a = 2, 7, and 61;
if n < 1,122,004,669,633, it is enough to test a = 2, 13, 23, and 1662803;
if n < 2,152,302,898,747, it is enough to test a = 2, 3, 5, 7, and 11;
if n < 3,474,749,660,383, it is enough to test a = 2, 3, 5, 7, 11, and 13;
if n < 341,550,071,728,321, it is enough to test a = 2, 3, 5, 7, 11, 13, and 17;
if n < 3,825,123,056,546,413,051, it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, and 23;
if n < 18,446,744,073,709,551,616 = 2^64, it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, and 37;
if n < 318,665,857,834,031,151,167,461, it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, and 37;
if n < 3,317,044,064,679,887,385,961,981, it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, and 41.
"""


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

        b = pow(a, d, x)
        if b in [1, x - 1]:
            continue

        if s == 1:
            return False

        for _ in range(s - 1):
            b = b * b % x
            if b == x - 1:
                break
        else:
            return False
    return True
