"""
Graham's scan is a method of finding the convex hull of a finite set of points in the plane with time complexity O(n log n).
It is named after Ronald Graham, who published the original algorithm in 1972. The algorithm finds all vertices of the convex hull ordered along its boundary.
It uses a stack to detect and remove concavities in the boundary efficiently.
"""

import sys


def tangent(x: int, y: int) -> tuple:
    if x == a:
        return 1, y
    if x > a:
        return 0, (y - b) / (x - a), x
    if x < a:
        return 2, (y - b) / (x - a), x


def isline(x: tuple, y: tuple, z: tuple) -> bool:  # are x, y, and z on the line?
    return (y[1] - x[1]) * (z[0] - y[0]) == (z[1] - y[1]) * (y[0] - x[0])


n = int(sys.stdin.readline())
coord = [tuple(map(int, sys.stdin.readline().split())) for _ in range(n)]
coord.sort(key=lambda x: (x[1], x[0]))
a, b = coord.pop(0)
coord.sort(key=lambda x: tangent(x[0], x[1]))
stack = [(a, b), coord[0]]
idx = 0
while idx < n - 2:
    idx += 1
    w1, w2 = coord[idx]
    while len(stack) >= 2:
        u1, u2 = stack[-2]
        v1, v2 = stack[-1]
        if (v1 - u1) * (w2 - v2) <= (v2 - u2) * (w1 - v1):
            stack.pop()
        else:
            break
    stack.append((w1, w2))
    if (len(stack) >= 3) and (isline(stack[-3], stack[-2], stack[-1])):
        stack.pop(-2)

if len(stack) >= 3:
    if isline(stack[-2], stack[-1], stack[0]):
        stack.pop()
