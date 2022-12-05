# BOJ 1197 최소 스패닝 트리

import sys
input = sys.stdin.readline

V, E = map(int, input().split())
P = [i for i in range(V + 1)]
G = sorted([tuple(map(int, input().split())) for _ in range(E)], key=lambda x: x[2])


def union(x, y):
    P[find(x)] = find(y)


def find(z):
    if z != P[z]:
        P[z] = find(P[z])
    return P[z]


ans = 0
cnt = 0
for u, v, w in G:
    if find(u) != find(v):
        union(u, v)
        ans += w
        cnt += 1
    
    if cnt == V - 1:
        print(ans)
        break
else:
    print(-1)
