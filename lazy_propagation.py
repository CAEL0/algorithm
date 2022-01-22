import sys
from math import log2, ceil

n = int(sys.stdin.readline())
height = ceil(log2(n))
tree = [0] * 2 ** (height + 1)
lazy = [0] * 2 ** (height + 1)

for i in range(n):
    tree[2 ** height + i] = int(sys.stdin.readline())

for h in range(height - 1, -1, -1):
    for i in range(2 ** h, 2 ** (h + 1)):
        tree[i] = tree[2 * i] + tree[2 * i + 1]


def summation(a, b):
    res = 0
    queue = [(a, b, 1)]
    while queue:
        a, b, idx = queue.pop()
        level = 2 ** int(log2(idx))
        length = (2 ** height) // level
        start = (idx % level) * length
        mid = start + length // 2

        if lazy[idx]:
            if length == 2:
                tree[2 * idx] += lazy[idx]
                tree[2 * idx + 1] += lazy[idx]
            else:
                lazy[2 * idx] += lazy[idx]
                lazy[2 * idx + 1] += lazy[idx]

            tree[idx] += lazy[idx] * length
            lazy[idx] = 0

        if (a == start) and (b - a + 1 == length):
            res += tree[idx]
        elif b < mid:
            queue.append((a, b, 2 * idx))
        elif mid <= a:
            queue.append((a, b, 2 * idx + 1))
        else:
            queue.append((a, mid - 1, 2 * idx))
            queue.append((mid, b, 2 * idx + 1))
    return res


def update(a, b, c):
    queue = [(a, b, 1)]
    while queue:
        a, b, idx = queue.pop()
        level = 2 ** int(log2(idx))
        length = (2 ** height) // level
        start = (idx % level) * length
        mid = start + length // 2

        if lazy[idx]:
            if length == 2:
                tree[2 * idx] += lazy[idx]
                tree[2 * idx + 1] += lazy[idx]
            else:
                lazy[2 * idx] += lazy[idx]
                lazy[2 * idx + 1] += lazy[idx]

            tree[idx] += lazy[idx] * length
            lazy[idx] = 0

        if (a == start) and (b - a + 1 == length):
            if length == 1:
                tree[idx] += c
            else:
                lazy[idx] = c

            while idx > 1:
                idx //= 2
                tree[idx] += length * c

        elif b < mid:
            queue.append((a, b, 2 * idx))
        elif mid <= a:
            queue.append((a, b, 2 * idx + 1))
        else:
            queue.append((a, mid - 1, 2 * idx))
            queue.append((mid, b, 2 * idx + 1))
