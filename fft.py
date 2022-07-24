"""
A fast Fourier transform (FFT) is an algorithm that computes the discrete Fourier transform (DFT) of a sequence, or its inverse (IDFT).
Fourier analysis converts a signal from its original domain (often time or space) to a representation in the frequency domain and vice versa.
The DFT is obtained by decomposing a sequence of values into components of different frequencies.
This operation is useful in many fields, but computing it directly from the definition is often too slow to be practical.
An FFT rapidly computes such transformations by factorizing the DFT matrix into a product of sparse (mostly zero) factors.
As a result, it manages to reduce the complexity of computing the DFT from O(N^2), which arises if one simply applies the definition of DFT,
to O(NlogN), where N is the data size.
The difference in speed can be enormous, especially for long data sets where N may be in the thousands or millions.
In the presence of round-off error, many FFT algorithms are much more accurate than evaluating the DFT definition directly or indirectly.
There are many different FFT algorithms based on a wide range of published theories, from simple complex-number arithmetic to group theory and number theory.
"""

# BOJ 1067 이동

from math import cos, sin, pi


def fft(arr, w):
    n = len(arr) // 2
    if n == 0:
        return
    
    even = []
    odd = []
    for i in range(n):
        even.append(arr[2 * i])
        odd.append(arr[2 * i + 1])
    
    ww = w * w
    fft(even, ww)
    fft(odd, ww)
    
    wk = complex(1, 0)
    for i in range(n):
        arr[i] = even[i] + wk * odd[i]
        arr[i + n] = even[i] - wk * odd[i]
        wk *= w


def multiply(a, b):
    n = 1
    while (n <= len(a)) or (n <= len(b)):
        n *= 2
    n *= 2

    a.extend([0] * (n - len(a)))
    b.extend([0] * (n - len(b)))
    w = complex(cos(2 * pi / n), sin(2 * pi / n))
    fft(a, w)
    fft(b, w)
    c = [a[i] * b[i] for i in range(n)]
    fft(c, 1 / w)
    for i in range(n):
        c[i] = round(c[i].real / n)
    return c

#--------------------------------------------------------------------------------

def fft(arr, inv):
    n = len(arr)
    j = 0
    for i in range(1, n):
        bit = n // 2
        while True:
            j ^= bit
            if j & bit:
                break
            bit //= 2
        if i < j:
            arr[i], arr[j] = arr[j], arr[i]
    
    i = 1
    while i < n:
        if inv:
            x = pi / i
        else:
            x = -pi / i
        w = complex(cos(x), sin(x))
        for j in range(0, n, 2 * i):
            wk = complex(1, 0)
            for k in range(i):
                tmp = arr[i + j + k] * wk
                arr[i + j + k] = arr[j + k] - tmp
                arr[j + k] += tmp
                wk *= w
        i *= 2


def multiply(a, b):
    n = 1
    while (n <= len(a)) or (n <= len(b)):
        n *= 2
    n *= 2

    a.extend([0] * (n - len(a)))
    b.extend([0] * (n - len(b)))
    fft(a, False)
    fft(b, False)
    c = [a[i] * b[i] for i in range(n)]
    fft(c, True)
    for i in range(n):
        c[i] = round(c[i].real / n)
    return c
