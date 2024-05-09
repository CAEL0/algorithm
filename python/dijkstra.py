# BOJ 1753 최단경로

import sys
from heapq import heappush, heappop
input = sys.stdin.readline

V, E = map(int, input().split())
K = int(input())
G = [[] for _ in range(V + 1)]

for _ in range(E):
    a, b, c = map(int, input().split())
    G[a].append((b, c))


def dijkstra(start):
    dist = [float('inf')] * (V + 1)
    dist[start] = 0
    hq = [(0, start)]
    while hq:
        cur_w, cur = heappop(hq)
        if dist[cur] == cur_w:
            for nxt, nxt_w in G[cur]:
                sum_w = cur_w + nxt_w
                if sum_w < dist[nxt]:
                    dist[nxt] = sum_w
                    heappush(hq, (sum_w, nxt))
    return dist


dist = dijkstra(K)
for i in range(1, V + 1):
    if dist[i] == float('inf'):
        print('INF')
    else:
        print(dist[i])
