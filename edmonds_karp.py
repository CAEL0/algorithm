"""
In computer science, the Edmonds–Karp algorithm is an implementation of the Ford–Fulkerson method for computing the maximum flow in a flow network in O(V * E ** 2) time.
The algorithm was first published by Yefim Dinitz (whose name is also transliterated "E. A. Dinic", notably as author of his early papers) in 1970
and independently published by Jack Edmonds and Richard Karp in 1972.
Dinic's algorithm includes additional techniques that reduce the running time to O(V ** 2 * E).
"""

# BOJ 2188 축사 배정

import sys
from collections import deque

n, m = map(int, sys.stdin.readline().split())
graph = [[0] * (n + 1) for _ in range(n + 1)]

for _ in range(m):
    start, end, capacity = map(int, sys.stdin.readline().split())
    graph[start][end] += capacity

ans = 0
while True:
    prev = [-1] * (n + 1)
    queue = deque([(1, float('inf'))])
    while queue:
        cur, res = queue.popleft()
        if graph[cur][-1]:
            res = min(res, graph[cur][-1])
            prev[-1] = cur
            break
        
        for nxt in range(2, n):
            if (prev[nxt] == -1) and graph[cur][nxt]:
                prev[nxt] = cur
                queue.append((nxt, min(res, graph[cur][nxt])))

        if prev[-1] != -1:
            break
    
    if prev[-1] == -1:
        break

    ans += res
    nxt = -1
    while True:
        cur = prev[nxt]
        graph[cur][nxt] -= res
        graph[nxt][cur] += res
        nxt = cur
        if nxt == 1:
            break

print(ans)

#--------------------------------------------------------------------------------

import sys
from collections import deque

n, m = map(int, sys.stdin.readline().split())
graph = [[] for _ in range(n + 1)]

for _ in range(m):
    start, end, capacity = map(int, sys.stdin.readline().split())
    graph[start].append([end, capacity])

ans = 0
while True:
    prev = [-1] * (n + 1)
    queue = deque([(1, float('inf'))])
    while queue:
        cur, res = queue.popleft()
        for nxt, capacity in graph[cur]:
            if nxt == n:
                res = min(res, capacity)
                prev[nxt] = cur
                break
               
            if prev[nxt] == -1:
                prev[nxt] = cur
                queue.append((nxt, min(res, capacity)))

        if prev[-1] != -1:
            break
    
    if prev[-1] == -1:
        break

    ans += res
    nxt = n
    while True:
        cur = prev[nxt]
        for i in range(len(graph[cur])):
            if graph[cur][i][0] == nxt:
                graph[cur][i][1] -= res
                if graph[cur][i][1] == 0:
                    graph[cur].remove([nxt, 0])
                break
        
        for i in range(len(graph[nxt])):
            if graph[nxt][i][0] == cur:
                graph[nxt][i][1] += res
                break
        else:
            graph[nxt].append([cur, res])

        nxt = cur
        if nxt == 1:
            break

print(ans)
