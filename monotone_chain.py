# BOJ 1708 볼록 껍질

import sys
input = sys.stdin.readline


def ccw(x1, y1, x2, y2, x3, y3):
    return (x2 - x1) * (y3 - y2) - (x3 - x2) * (y2 - y1)


N = int(input())
A = sorted([tuple(map(int, input().split())) for _ in range(N)])
S = [A[0], A[1]]
for i in range(2, N):
    while (len(S) > 1) and (ccw(*S[-2], *S[-1], *A[i]) <= 0):
        S.pop()
    S.append(A[i])

SS = [A[-1], A[-2]]
for i in range(N - 3, -1, -1):
    while (len(SS) > 1) and (ccw(*SS[-2], *SS[-1], *A[i]) <= 0):
        SS.pop()
    SS.append(A[i])

for i in range(1, len(SS) - 1):
    S.append(SS[i])

print(len(S))
