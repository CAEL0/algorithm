"""
he Shortest Path Faster Algorithm (SPFA) is an improvement of the Bellman–Ford algorithm which computes single-source shortest paths in a weighted directed graph.
The algorithm is believed to work well on random sparse graphs and is particularly suitable for graphs that contain negative-weight edges.
However, the worst-case complexity of SPFA is the same as that of Bellman–Ford, so for graphs with nonnegative edge weights Dijkstra's algorithm is preferred.
The SPFA algorithm was first published by Edward F. Moore in 1959, as a generalization of breadth first search;
SPFA is Moore's “Algorithm D.” The name, “Shortest Path Faster Algorithm (SPFA),” was given by FanDing Duan, a Chinese researcher who rediscovered the algorithm in 1994.
"""

import sys
from collections import deque

n, m = map(int, sys.stdin.readline().split())
graph = [[] for _ in range(n + 1)]
for _ in range(m):
    a, b, t = map(int, sys.stdin.readline().split())
    graph[a].append((b, t))

res = [float('inf') for _ in range(n + 1)]
visit = [0] * (n + 1)

res[1] = 0
queue = deque([1])
while queue:
    cur = queue.popleft()
    visit[cur] = 0

    for nxt, weight in graph[cur]:
        if res[nxt] > res[cur] + weight:
            res[nxt] = res[cur] + weight
            if not visit[nxt]:
                queue.append(nxt)
                visit[nxt] = 1
