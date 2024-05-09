# BOJ 1717 집합의 표현

import sys
input = sys.stdin.readline

N, Q = map(int, input().split())
P = [i for i in range(N + 1)]


def union(x, y):
    P[find(x)] = find(y)


def find(z):
    u = z
    v = P[u]
    while u != v:
        u, v = v, P[v]
    P[z] = v
    return v


for _ in range(Q):
    o, x, y = map(int, input().split())
    if o:
        print(['NO', 'YES'][find(x) == find(y)])
    else:
        union(x, y)
