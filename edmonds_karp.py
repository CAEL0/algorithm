"""
In computer science, the Edmonds–Karp algorithm is an implementation of the Ford–Fulkerson method for computing the maximum flow in a flow network in O(V * E ** 2) time.
The algorithm was first published by Yefim Dinitz (whose name is also transliterated "E. A. Dinic", notably as author of his early papers) in 1970
and independently published by Jack Edmonds and Richard Karp in 1972.
Dinic's algorithm includes additional techniques that reduce the running time to O(V ** 2 * E).
"""

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
    prev[1] = 0
    queue = deque([(1, float('inf'))])
    while queue:
        cur, res = queue.popleft()
        
        for nxt in range(2, n + 1):
            if (nxt == n) and graph[cur][-1]:
                res = min(res, graph[cur][-1])
                prev[-1] = cur
                break

            if (prev[nxt] == -1) and graph[cur][nxt]:
                prev[nxt] = cur
                queue.append((nxt, min(res, graph[cur][nxt])))

        if prev[-1] != -1:
            break
    
    if prev[-1] == -1:
        break

    ans += res
    while True:
        cur = prev[nxt]
        graph[cur][nxt] -= res
        graph[nxt][cur] += res
        nxt = cur
        if nxt == 1:
            break

print(ans)
