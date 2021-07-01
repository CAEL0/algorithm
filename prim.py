"""
In computer science, Prim's (also known as Jarník's) algorithm is a greedy algorithm that finds a minimum spanning
tree for a weighted undirected graph. This means it finds a subset of the edges that forms a tree that includes every
vertex, where the total weight of all the edges in the tree is minimized. The algorithm operates by building this
tree one vertex at a time, from an arbitrary starting vertex, at each step adding the cheapest possible connection
from the tree to another vertex.
"""

import sys
from heapq import heappush, heappop
from collections import defaultdict

V, E = map(int, sys.stdin.readline().split())  # V : the number of vertices, E : the number of edges
visit = [0] * (V + 1)
board = defaultdict(list)
for _ in range(E):
    start, end, weight = map(int, sys.stdin.readline().split())  # start node -- weight -- end node
    board[start].append((weight, end))
    board[end].append((weight, start))


def prim(graph: defaultdict) -> int:
    res = 0
    adj = []
    new = 1
    visit[1] = 1
    for _ in range(V - 1):
        for (w, node) in graph[new]:
            if visit[node] == 0:
                heappush(adj, (w, node))

        while True:
            (w, new) = heappop(adj)
            if visit[new] == 0:
                visit[new] = 1
                res += w
                break

    return res
