# BOJ 2252 줄 세우기

import sys
from collections import deque
input = sys.stdin.readline

N, M = map(int, input().split())
G = [[] for _ in range(N + 1)]
ind = [0] * (N + 1)
for _ in range(M):
    a, b = map(int, input().split())
    G[a].append(b)
    ind[b] += 1

dq = deque([i for i in range(1, N + 1) if ind[i] == 0])
while dq:
    i = dq.popleft()
    print(i)
    for j in G[i]:
        ind[j] -= 1
        if ind[j] == 0:
            dq.append(j)
