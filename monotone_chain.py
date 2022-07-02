# BOJ 1708 볼록 껍질

import sys
input = sys.stdin.readline


def ccw(x1, y1, x2, y2, x3, y3):
    return (x2 - x1) * (y3 - y2) - (x3 - x2) * (y2 - y1)


n = int(input())
coord = sorted([tuple(map(int, input().split())) for _ in range(n)])
coord.sort()
stack1 = [coord[0], coord[1]]
for i in range(2, n):
    while (len(stack1) > 1) and (ccw(*stack1[-2], *stack1[-1], *coord[i]) <= 0):
        stack1.pop()
    stack1.append(coord[i])

stack2 = [coord[-1], coord[-2]]
for i in range(n - 3, -1, -1):
    while (len(stack2) > 1) and (ccw(*stack2[-2], *stack2[-1], *coord[i]) <= 0):
        stack2.pop()
    stack2.append(coord[i])

print(len(stack1) + len(stack2) - 2)
