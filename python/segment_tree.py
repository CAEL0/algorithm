# BOJ 2042 구간 합 구하기

import sys
from math import log2, ceil
input = sys.stdin.readline

n = int(input())
height = ceil(log2(n))
z = 2 ** height
tree = [0] * 2 * z

for i in range(n):
    tree[z + i] = int(input())

for h in range(height - 1, -1, -1):
    for i in range(2 ** h, 2 ** (h + 1)):
        tree[i] = tree[2 * i] + tree[2 * i + 1]


def summation(a, b):
    res = 0
    a += z - 1
    b += z - 1
    while a <= b:
        if a % 2:
            res += tree[a]
            a += 1
        if b % 2 == 0:
            res += tree[b]
            b -= 1
        a //= 2
        b //= 2
    return res


def update(k, c):
    idx = z + k - 1
    gap = tree[idx] - c
    while idx >= 1:
        tree[idx] -= gap
        idx //= 2

#--------------------------------------------------------------------------------

def maximum(a, b):
    res = 0
    a += z - 1
    b += z - 1
    while a <= b:
        if a % 2:
            res = max(res, tree[a])
            a += 1
        if b % 2 == 0:
            res = max(res, tree[b])
            b -= 1
        a //= 2
        b //= 2
    return res


def update(k, c):
    idx = z + k - 1
    tree[idx] = c
    while idx > 1:
        idx //= 2
        tree[idx] = max(tree[2 * idx], tree[2 * idx + 1])
