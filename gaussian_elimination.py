# BOJ 22940 선형 연립 방정식

import sys
from math import lcm
input = sys.stdin.readline

n = int(input())
equation = [[*map(int, input().split())] for _ in range(n)]

for z in range(n - 1):
    l = lcm(*[equation[i][z] for i in range(n - z)])
    for i in range(n - z):
        k = l // equation[i][z]
        for j in range(z, n + 1):
            equation[i][j] *= k

    for i in range(n - z - 1):
        for j in range(z, n + 1):
            equation[i][j] -= equation[- z - 1][j]

ans = []
for z in range(n):
    x = equation[z][-1] // equation[z][- z - 2]
    ans.append(x)

    for i in range(z + 1, n):
        equation[i][-1] -= x * equation[i][- z - 2]

print(*reversed(ans))
