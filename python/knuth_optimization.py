# BOJ 13974 파일 합치기 2

import sys
input = sys.stdin.readline

for _ in range(int(input())):
    N = int(input())
    A = [*map(int, input().split())]
    pre = [0] * (N + 1)
    for i in range(N):
        pre[i + 1] = pre[i] + A[i]
    
    dp = [[0] * N for _ in range(N)]
    kk = [[0] * N for _ in range(N)]
    for i in range(-1, N - 1):
        j = i + 1
        kk[i][j] = j
    
    for l in range(2, N + 1):
        for i in range(-1, N - l):
            j = i + l
            mn = float('inf')
            for k in range(max(i + 1, kk[i][j - 1]), min(j, kk[i + 1][j] + 1)):
                res = dp[i][k] + dp[k][j]
                if mn > res:
                    mn = res
                    idx = k

            mn += pre[j + 1] - pre[i + 1]
            dp[i][j] = mn
            kk[i][j] = idx
    
    print(dp[-1][-1])
