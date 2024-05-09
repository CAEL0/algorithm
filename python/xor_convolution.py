# BOJ 14878 부분 수열 XOR합

import sys
input = sys.stdin.readline


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
        for j in range(0, n, 2 * i):
            for k in range(i):
                tmp = arr[i + j + k]
                arr[i + j + k] = arr[j + k] - tmp
                arr[j + k] += tmp
        i *= 2

    if inv:
        for i in range(n):
            arr[i] //= n


def xor(a):
    n = 1
    while n <= len(a):
        n *= 2
    n *= 2

    a.extend([0] * (n - len(a)))
    fft(a, False)
    c = [a[i] * a[i] for i in range(n)]
    fft(c, True)
    return c


n = int(input())
arr = [*map(int, input().split())]
cnt = [0] * (2 ** 16)
cnt[0] = 1
tmp = 0
for i in arr:
    tmp ^= i
    cnt[tmp] += 1

res = xor(cnt[:])
res[0] = 0
for i in range(1, len(cnt)):
    res[0] += cnt[i] * cnt[i - 1] // 2
    res[i] //= 2

mx = max(res)
for i in range(len(res)):
    if res[i] == mx:
        print(i, mx)
        break
