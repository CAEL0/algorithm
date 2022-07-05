# BOJ 13974 파일 합치기 2

import sys
input = sys.stdin.readline

for _ in range(int(input())):
    n = int(input())
    a = [*map(int, input().split())]
    aa = [0] * (n + 1)
    for i in range(n):
        aa[i + 1] = aa[i] + a[i]
    
    dp = [[0] * n for _ in range(n)]
    kk = [[0] * n for _ in range(n)]
    for i in range(-1, n - 1):
        j = i + 1
        kk[i][j] = j
    
    for l in range(2, n + 1):
        for i in range(-1, n - l):
            j = i + l
            mn = float('inf')
            for k in range(max(i + 1, kk[i][j - 1]), min(j, kk[i + 1][j] + 1)):
                res = dp[i][k] + dp[k][j]
                if mn > res:
                    mn = res
                    idx = k

            mn += aa[j + 1] - aa[i + 1]
            dp[i][j] = mn
            kk[i][j] = idx
    
    print(dp[-1][-1])
