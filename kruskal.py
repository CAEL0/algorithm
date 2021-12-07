"""
Kruskal's algorithm finds a minimum spanning forest of an undirected edge-weighted graph. If the graph is
connected, it finds a minimum spanning tree. (A minimum spanning tree of a connected graph is a subset of the edges
that forms a tree that includes every vertex, where the sum of the weights of all the edges in the tree is minimized.
For a disconnected graph, a minimum spanning forest is composed of a minimum spanning tree for each connected
component.) It is a greedy algorithm in graph theory as in each step it adds the next lowest-weight edge that will
not form a cycle to the minimum spanning forest.
"""

import sys

v, e = map(int, sys.stdin.readline().split())
parent = [i for i in range(v + 1)]
board = sorted([tuple(map(int, sys.stdin.readline().split())) for _ in range(e)], key=lambda x: x[2])


def union(x, y):
    parent[find(x)] = find(y)


def find(z):
    if z != parent[z]:
        parent[z] = find(parent[z])
    return parent[z]


def kruskal(graph):
    res = 0
    idx = 0
    for x, y, w in graph:
        if find(x) != find(y):
            union(x, y)
            res += w
            idx += 1

        if idx == v - 1:
            return res

    return -1
