# BOJ 13263 나무 자르기

import sys
input = sys.stdin.readline

N = int(input())
A = [*map(int, input().split())]
B = [*map(int, input().split())]
S = [(B[0], 0)]

for i in range(1, N):
    left = 0
    right = len(S) - 1
    while left < right:
        mid = (left + right) // 2
        if S[mid + 1][1] - S[mid][1] <= A[i] * (S[mid][0] - S[mid + 1][0]):
            left = mid + 1
        else:
            right = mid
    
    S.append((B[i], S[left][0] * a[i] + S[left][1]))
    while len(S) > 2:
        if (S[-1][1] - S[-2][1]) * (S[-3][0] - S[-2][0]) >= (S[-2][1] - S[-3][1]) * (S[-2][0] - S[-1][0]):
            break
        S.pop(-2)

print(S[-1][1])
