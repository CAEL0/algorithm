"""
In computer science, a segment tree, also known as a statistic tree, is a tree data structure used for storing
information about intervals, or segments. It allows querying which of the stored segments contain a given point. It
is, in principle, a static structure; that is, it's a structure that cannot be modified once it's built. A similar
data structure is the interval tree. A segment tree for a set I of n intervals uses O(n log n) storage and can be
built in O(n log n) time. Segment trees support searching for all the intervals that contain a query point in time O(
log n + k), k being the number of retrieved intervals or segments.
"""

import sys
from math import log2, ceil

N = int(sys.stdin.readline())
H = ceil(log2(N))
tree = [0] * 2 ** (H + 1)

for i in range(N):
    tree[2 ** H + i] = int(sys.stdin.readline())

for h in range(H - 1, -1, -1):
    for i in range(2 ** h, 2 ** (h + 1)):
        tree[i] = tree[2 * i] + tree[2 * i + 1]


def partial_sum(r: int, a: int, b: int) -> int:
    level = 2 ** int(log2(r))
    length = (2 ** H) // level
    if length == 1:
        return tree[r]

    start = (r % level) * length
    mid = start + length // 2
    if (a == start) and (b == start + length - 1):
        return tree[r]

    if b < mid:
        return partial_sum(2 * r, a, b)

    if mid <= a:
        return partial_sum(2 * r + 1, a, b)

    return partial_sum(2 * r, a, mid - 1) + partial_sum(2 * r + 1, mid, b)


def change(r: int, c: int) -> None:
    idx = 2 ** H + r-1
    gap = tree[idx] - c
    while idx >= 1:
        tree[idx] -= gap
        idx //= 2
