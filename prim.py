# BOJ 1197 최소 스패닝 트리

import sys
from heapq import heappush, heappop
input = sys.stdin.readline

n, m = map(int, input().split())
graph = [[] for _ in range(n + 1)]
for _ in range(m):
    a, b, c = map(int, input().split())
    graph[a].append((c, b))
    graph[b].append((c, a))

visit = [0] * (n + 1)
visit[1] = 1
ans = 0
new = 1
hq = []
for _ in range(n - 1):
    for (w, node) in graph[new]:
        if not visit[node]:
            heappush(hq, (w, node))

    while True:
        (w, new) = heappop(hq)
        if not visit[new]:
            visit[new] = 1
            ans += w
            break

print(ans)
