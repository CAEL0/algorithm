# BOJ 2098 외판원 순회

import sys
input = sys.stdin.readline

n = int(input())
graph = [[*map(int, sys.stdin.readline().split())] for _ in range(n)]
dp = [[-1] * (2 ** n) for _ in range(n)]


def f(cur, mask):
    if dp[cur][mask] != -1:
        return dp[cur][mask]

    if mask == 2 ** n - 1:
        if graph[cur][0]:
            return graph[cur][0]
        return float('inf')

    ret = float('inf')
    for nxt in range(n):
        if (not mask & (1 << nxt)) and graph[cur][nxt]:
            ret = min(ret, f(nxt, mask | (1 << nxt)) + graph[cur][nxt])
    
    dp[cur][mask] = ret
    return ret


print(f(0, 1))
