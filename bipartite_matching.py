# BOJ 2188 축사 배정

import sys


def dfs(cur):
    visit[cur] = 1
    for nxt in graph[cur]:
        if not b[nxt] or (not visit[b[nxt]] and dfs(b[nxt])):
            b[nxt] = cur
            return 1
    return 0


n, m = map(int, sys.stdin.readline().split())
graph = [[] for _ in range(n + 1)]

for i in range(1, n + 1):
    data = list(map(int, sys.stdin.readline().split()))
    for j in range(1, data[0] + 1):
        graph[i].append(data[j])

b = [0] * (m + 1)
ans = 0

for i in range(1, n + 1):
    visit = [0] * (n + 1)
    ans += dfs(i)

print(ans)
