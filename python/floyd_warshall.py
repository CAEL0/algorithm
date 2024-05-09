# BOJ 11404 플로이드

import sys
input = sys.stdin.readline

V = int(input())
E = int(input())
G = [[] for _ in range(V + 1)]

for _ in range(E):
    u, v, w = map(int, input().split())
    G[u].append((v, w))


def floyd_warshall():
    dist = [[float('inf')] * (V + 1) for _ in range(V + 1)]
    for u in range(1, V + 1):
        dist[u][u] = 0
        for v, w in G[u]:
            dist[u][v] = min(dist[u][v], w)

    for k in range(1, V + 1):
        for i in range(1, V + 1):
            for j in range(1, V + 1):
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
    return dist


res = floyd_warshall()
for i in range(1, V + 1):
    for j in range(1, V + 1):
        if res[i][j] == float('inf'):
            print(0, end=' ')
        else:
            print(res[i][j], end=' ')
    print()
