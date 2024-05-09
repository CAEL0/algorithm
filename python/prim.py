# BOJ 1197 최소 스패닝 트리

import sys
from heapq import heappush, heappop
input = sys.stdin.readline

V, E = map(int, input().split())
G = [[] for _ in range(V + 1)]
for _ in range(E):
    u, v, w = map(int, input().split())
    G[u].append((w, v))
    G[v].append((w, u))

vst = [0] * (V + 1)
vts[1] = 1
ans = 0
cur = 1
hq = []
for _ in range(V - 1):
    for (w, nxt) in G[cur]:
        if not vst[nxt]:
            heappush(hq, (w, nxt))

    while True:
        (w, cur) = heappop(hq)
        if not vst[cur]:
            vst[cur] = 1
            ans += w
            break

print(ans)
