# BOJ 2188 축사 배정

import sys
input = sys.stdin.readline


def dfs(cur):
    vst[cur] = 1
    for nxt in G[cur]:
        if not B[nxt] or (not vst[B[nxt]] and dfs(B[nxt])):
            B[nxt] = cur
            return 1
    return 0


N, M = map(int, input().split())
G = [[] for _ in range(N + 1)]

for i in range(1, N + 1):
    arr = [*map(int, input().split())]
    for j in range(1, arr[0] + 1):
        G[i].append(arr[j])

B = [0] * (M + 1)
ans = 0

for i in range(1, N + 1):
    vst = [0] * (N + 1)
    ans += dfs(i)

print(ans)
