# BOJ 1912 연속합

import sys
input = sys.stdin.readline

n = int(input())
arr = [*map(int, input().split())]
ans = [arr[0]]
for i in range(1, n):
    ans.append(max(ans[-1] + arr[i], arr[i]))

print(max(ans))
