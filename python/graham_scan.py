# BOJ 1708 볼록 껍질

import sys
input = sys.stdin.readline


def tangent(z):
    x, y = z
    if x == a:
        return 1, y
    if x > a:
        return 0, (y - b) / (x - a), x
    if x < a:
        return 2, (y - b) / (x - a), -x


def ccw(x1, y1, x2, y2, x3, y3):
    return (x2 - x1) * (y3 - y2) - (x3 - x2) * (y2 - y1)


n = int(input())
coord = [tuple(map(int, input().split())) for _ in range(n)]
coord.sort(key=lambda x: (-x[1], -x[0]))
a, b = coord.pop()
coord.sort(key=tangent)

stack = [(a, b), coord[0]]
for i in range(1, n - 1):
    while (len(stack) >= 2) and (ccw(*stack[-2], *stack[-1], *coord[i]) <= 0):
        stack.pop()
    stack.append(coord[i])

if (len(stack) >= 3) and (ccw(*stack[-2], *stack[-1], *stack[0]) <= 0):
    stack.pop()
