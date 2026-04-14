# BOJ 13034 다각형 게임

import sys
input = sys.stdin.readline

n = int(input())

grundy = [0] * (n + 1)
for i in range(2, n + 1):
    v = [0] * (i + 1)
    left = 0
    right = i - 2
    while left <= right:
        v[grundy[left] ^ grundy[right]] = True
        left += 1
        right -= 1
    
    mex = 0
    while v[mex]:
        mex += 1
    
    grundy[i] = mex

print(2 if grundy[n] == 0 else 1)
