"""
In arithmetic and computer programming, the extended Euclidean algorithm is an extension to the Euclidean
algorithm, and computes, in addition to the greatest common divisor (gcd) of integers a and b, also the coefficients
of Bézout's identity, which are integers x and y such that ax + by = gcd(a, b).
"""

# BOJ 14565 역원(Inverse) 구하기

def extended_gcd(a, b):
    x0, x1, y0, y1 = 1, 0, 0, 1
    while b != 0:
        n, a, b = a // b, b, a % b
        x0, x1 = x1, x0 - n * x1
        y0, y1 = y1, y0 - n * y1
    return x0, y0
