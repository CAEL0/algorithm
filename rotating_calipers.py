# BOJ 10254 고속도로

import sys
input = sys.stdin.readline


def ccw(x1, y1, x2, y2, x3, y3):
    return (x2 - x1) * (y3 - y2) - (x3 - x2) * (y2 - y1)


for _ in range(int(input())):
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
    
    m = len(stack)
    a = 0
    b = 1
    mx = (stack[a][0] - stack[b][0]) ** 2 + (stack[a][1] - stack[b][1]) ** 2
    ans = [*stack[a], *stack[b]]
    for _ in range(2 * m):
        c = (a + 1) % m
        d = (b + 1) % m
        if (stack[c][0] - stack[a][0]) * (stack[b][1] - stack[d][1]) > (stack[b][0] - stack[d][0]) * (stack[c][1] - stack[a][1]):
            a = c
        else:
            b = d
        
        res = (stack[a][0] - stack[b][0]) ** 2 + (stack[a][1] - stack[b][1]) ** 2
        if mx < res:
            mx = res
            ans = [*stack[a], *stack[b]]
    
    print(*ans)
