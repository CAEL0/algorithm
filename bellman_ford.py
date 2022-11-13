# BOJ 11657 타임머신

import sys
input = sys.stdin.readline

V, E = map(int, input().split())
G = [[] for _ in range(V + 1)]
for _ in range(E):
    u, v, w = map(int, input().split())
    G[u].append((v, w))


def bellman_ford(start):
    dist = [float('inf')] * (V + 1)
    dist[start] = 0
    for _ in range(V - 1):
        for u in range(1, V + 1):
            for v, w in G[u]:
                dist[v] = min(dist[v], dist[u] + w)
    return dist


res = bellman_ford(1)

for u in range(1, V + 1):
    for v, w in G[u]:
        if res[v] > res[u] + w:
            print(-1)
            exit()

for i in range(2, V + 1):
    if res[i] == float('inf'):
        print(-1)
    else:
        print(res[i])
