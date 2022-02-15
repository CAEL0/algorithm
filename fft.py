"""
A fast Fourier transform (FFT) is an algorithm that computes the discrete Fourier transform (DFT) of a sequence, or its inverse (IDFT).
Fourier analysis converts a signal from its original domain (often time or space) to a representation in the frequency domain and vice versa.
The DFT is obtained by decomposing a sequence of values into components of different frequencies.
This operation is useful in many fields, but computing it directly from the definition is often too slow to be practical.
An FFT rapidly computes such transformations by factorizing the DFT matrix into a product of sparse (mostly zero) factors.
As a result, it manages to reduce the complexity of computing the DFT from O(N^2), which arises if one simply applies the definition of DFT, to O(NlogN), where N is the data size.
The difference in speed can be enormous, especially for long data sets where N may be in the thousands or millions.
In the presence of round-off error, many FFT algorithms are much more accurate than evaluating the DFT definition directly or indirectly.
There are many different FFT algorithms based on a wide range of published theories, from simple complex-number arithmetic to group theory and number theory.
"""

import sys
from math import cos, sin, pi


def fft(coef, w):
    n = len(coef)
    if n == 1:
        return coef
    
    even = [0] * (n // 2)
    odd = [0] * (n // 2)
    for i in range(n // 2):
        even[i] = coef[2 * i]
        odd[i] = coef[2 * i + 1]
    
    ww = w * w
    fe = fft(even, ww)
    fo = fft(odd, ww)
    
    res = [0] * n
    wk = complex(1, 0)
    for i in range(n // 2):
        res[i] = fe[i] + wk * fo[i]
        wk *= w
    
    for i in range(n // 2):
        res[i + n // 2] = fe[i] + wk * fo[i]
        wk *= w
    return res


def multiply(a, b):
    n = 1
    while (n <= len(a)) or (n <= len(b)):
        n *= 2
    n *= 2

    a.extend([0] * (n - len(a)))
    b.extend([0] * (n - len(b)))
    w = complex(cos(2 * pi / n), sin(2 * pi / n))
    fa = fft(a, w)
    fb = fft(b, w)
    c = [fa[i] * fb[i] for i in range(n)]
    fc = fft(c, 1 / w)
    for i in range(n):
        fc[i] = round(fc[i].real / n)
    return fc
