"""
In computer science, Prim's (also known as Jarník's) algorithm is a greedy algorithm that finds a minimum spanning tree for a weighted undirected graph.
This means it finds a subset of the edges that forms a tree that includes every vertex, where the total weight of all the edges in the tree is minimized.
The algorithm operates by building this tree one vertex at a time, from an arbitrary starting vertex,
at each step adding the cheapest possible connection from the tree to another vertex.
"""

import sys
from heapq import heappush, heappop

n, m = map(int, sys.stdin.readline().split())
graph = [[] for _ in range(n + 1)]
for _ in range(m):
    a, b, c = map(int, sys.stdin.readline().split())
    graph[a].append((c, b))
    graph[b].append((c, a))

visit = [0] * (n + 1)
visit[1] = 1
ans = 0
new = 1
hq = []
for _ in range(n - 1):
    for (w, node) in graph[new]:
        if visit[node] == 0:
            heappush(hq, (w, node))

    while True:
        (w, new) = heappop(hq)
        if visit[new] == 0:
            visit[new] = 1
            ans += w
            break

print(ans)
