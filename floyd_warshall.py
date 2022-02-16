"""
In computer science, the Floyd–Warshall algorithm (also known as Floyd's algorithm, the Roy–Warshall algorithm, the Roy–Floyd algorithm, or the WFI algorithm)
is an algorithm for finding shortest paths in a directed weighted graph with positive or negative edge weights (but with no negative cycles).
A single execution of the algorithm will find the lengths (summed weights) of shortest paths between all pairs of vertices.
Although it does not return details of the paths themselves, it is possible to reconstruct the paths with simple modifications to the algorithm. 
Versions of the algorithm can also be used for finding the transitive closure of a relation R, or (in connection with the Schulze voting system)
widest paths between all pairs of vertices in a weighted graph.
"""

import sys
from collections import defaultdict

v, e = map(int, sys.stdin.readline().split())
graph = defaultdict(dict)

for _ in range(e):
    a, b, c = map(int, sys.stdin.readline().split())
    if b in graph[a].keys():
        graph[a][b] = min(graph[a][b], c)
    else:
        graph[a][b] = c


def floyd_warshall(graph):
    res = [[float('inf')] * (v + 1) for _ in range(v + 1)]
    for start in graph.keys():
        res[start][start] = 0
        for end in graph[start].keys():
            res[start][end] = min(res[start][end], graph[start][end])

    for k in range(1, v + 1):
        for i in range(1, v + 1):
            for j in range(1, v + 1):
                res[i][j] = min(res[i][j], res[i][k] + res[k][j])
    return res
