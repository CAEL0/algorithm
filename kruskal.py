"""
Kruskal's algorithm finds a minimum spanning forest of an undirected edge-weighted graph. If the graph is
connected, it finds a minimum spanning tree. (A minimum spanning tree of a connected graph is a subset of the edges
that forms a tree that includes every vertex, where the sum of the weights of all the edges in the tree is minimized.
For a disconnected graph, a minimum spanning forest is composed of a minimum spanning tree for each connected
component.) It is a greedy algorithm in graph theory as in each step it adds the next lowest-weight edge that will
not form a cycle to the minimum spanning forest.
"""

import sys

V, E = map(int, sys.stdin.readline().split())  # V : the number of vertices, E : the number of edges
board = []
for _ in range(E):
    start, end, weight = map(int, sys.stdin.readline().split())  # start node -- weight -- end node
    board.append((weight, start, end))
board.sort()
parent = [i for i in range(V + 1)]


def union(x: int, y: int) -> None:
    parent[find(x)] = find(y)


def find(z: int) -> int:
    if z != parent[z]:
        parent[z] = find(parent[z])
    return parent[z]


def kruskal(graph: list[tuple]) -> int:
    res = 0
    idx = 0
    for (w, x, y) in graph:
        if find(x) != find(y):
            union(x, y)
            res += w
            idx += 1

        if idx == V - 1:
            break

    return res
