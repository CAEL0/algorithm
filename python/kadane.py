# BOJ 1912 연속합

import sys
input = sys.stdin.readline

N = int(input())
A = [*map(int, input().split())]
res = [A[0]]
for i in range(1, N):
    res.append(max(res[-1] + A[i], A[i]))

print(max(res))
