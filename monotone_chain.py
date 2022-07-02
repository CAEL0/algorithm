# BOJ 1708 볼록 껍질

import sys
input = sys.stdin.readline


def ccw(x1, y1, x2, y2, x3, y3):
    return (x2 - x1) * (y3 - y2) - (x3 - x2) * (y2 - y1)


n = int(input())
coord = sorted([tuple(map(int, input().split())) for _ in range(n)])
stack = [coord[0], coord[1]]
for i in range(2, n):
    while (len(stack) > 1) and (ccw(*stack[-2], *stack[-1], *coord[i]) <= 0):
        stack.pop()
    stack.append(coord[i])

stack_ = [coord[-1], coord[-2]]
for i in range(n - 3, -1, -1):
    while (len(stack_) > 1) and (ccw(*stack_[-2], *stack_[-1], *coord[i]) <= 0):
        stack_.pop()
    stack_.append(coord[i])

for i in range(1, len(stack_) - 1):
    stack.append(stack_[i])

print(len(stack))
