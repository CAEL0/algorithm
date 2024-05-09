# BOJ 11658 구간 합 구하기 3

import sys
input = sys.stdin.readline


def update(i, j, v):
    k = i
    while j < N + 1:
        while i < N + 1:
            fw[i][j] += v
            i += i & -i
        j += j & -j
        i = k


def summation(i, j):
    ret = 0
    k = i
    while j > 0:
        while i > 0:
            ret += fw[i][j]
            i -= i & -i
        j -= j & -j
        i = k
    return ret


N, Q = map(int, input().split())
fw = [[0] * (N + 1) for _ in range(N + 1)]

for i in range(N):
    row = [*map(int, input().split())]
    for j in range(N):
        update(i + 1, j + 1, row[j])

for _ in range(Q):
    query = [*map(int, input().split())]
    if query[0]:
        x1, y1, x2, y2 = query[1:]
        print(summation(x2, y2) - summation(x2, y1 - 1) - summation(x1 - 1, y2) + summation(x1 - 1, y1 - 1))
    else:
        x, y, c = query[1:]
        update(x, y, c - summation(x, y) + summation(x, y - 1) + summation(x - 1, y) - summation(x - 1, y - 1))
