# BOJ 13263 나무 자르기

import sys
input = sys.stdin.readline

n = int(input())
a = [*map(int, input().split())]
b = [*map(int, input().split())]
stack = [(b[0], 0)]

for i in range(1, n):
    left = 0
    right = len(stack) - 1
    while left < right:
        mid = (left + right) // 2
        if stack[mid + 1][1] - stack[mid][1] <= a[i] * (stack[mid][0] - stack[mid + 1][0]):
            left = mid + 1
        else:
            right = mid
    
    stack.append((b[i], stack[left][0] * a[i] + stack[left][1]))
    while len(stack) > 2:
        if (stack[-1][1] - stack[-2][1]) * (stack[-3][0] - stack[-2][0]) >= (stack[-2][1] - stack[-3][1]) * (stack[-2][0] - stack[-1][0]):
            break
        stack.pop(-2)

print(stack[-1][1])
