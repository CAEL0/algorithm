# BOJ 17469 트리의 색깔과 쿼리

import sys
input = sys.stdin.readline


def find(c):
    u = c
    v = dsu[u]
    while u != v:
        u, v = v, dsu[v]
    dsu[c] = v
    return v


N, Q = map(int, input().split())
Q += N - 1
parent = [0] * (N + 1)
dsu = [i for i in range(N + 1)]
color = [set() for _ in range(N + 1)]
query = [[0] * 3 for _ in range(Q)]

for i in range(2, N + 1):
    parent[i] = int(input())

for i in range(1, N + 1):
    color[i].add(int(input()))

for i in range(Q):
    x, a = map(int, input().split())
    query[i][0] = x
    query[i][1] = a

for i in range(Q - 1, -1, -1):
    if query[i][0] == 1:
        u = query[i][1]
        v = parent[u]
        u = find(u)
        v = find(v)
        if len(color[u]) < len(color[v]):
            u, v = v, u
        
        dsu[v] = u
        for c in color[v]:
            color[u].add(c)
        
        color[v].clear()
    else:
        query[i][2] = len(color[find(query[i][1])])

for i in range(Q):
    if query[i][0] == 2:
        print(query[i][2])
