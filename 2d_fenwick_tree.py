# BOJ 11658 - 구간 합 구하기 3

import sys


def update(i, j, value):
    k = i
    while j < n + 1:
        while i < n + 1:
            fenwick_tree[i][j] += value
            i += i & -i
        j += j & -j
        i = k


def summation(i, j):
    res = 0
    k = i
    while j > 0:
        while i > 0:
            res += fenwick_tree[i][j]
            i -= i & -i
        j -= j & -j
        i = k
    return res


n, m = map(int, sys.stdin.readline().split())
fenwick_tree = [[0] * (n + 1) for _ in range(n + 1)]

for x in range(n):
    arr = list(map(int, sys.stdin.readline().split()))
    for y in range(n):
        update(x + 1, y + 1, arr[y])

for _ in range(m):
    operation = list(map(int, sys.stdin.readline().split()))
    if operation[0]:
        x1, y1, x2, y2 = operation[1:]
        print(summation(x2, y2) - summation(x2, y1 - 1) - summation(x1 - 1, y2) + summation(x1 - 1, y1 - 1))
    else:
        x, y, c = operation[1:]
        update(x, y, c - summation(x, y) + summation(x, y - 1) + summation(x - 1, y) - summation(x - 1, y - 1))
