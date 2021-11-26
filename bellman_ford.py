"""
The Bellman–Ford algorithm is an algorithm that computes shortest paths from a single source vertex to all of the
other vertices in a weighted digraph.[1] It is slower than Dijkstra's algorithm for the same problem,
but more versatile, as it is capable of handling graphs in which some of the edge weights are negative numbers. The
algorithm was first proposed by Alfonso Shimbel (1955), but is instead named after Richard Bellman and Lester Ford
Jr., who published it in 1958 and 1956, respectively.[2] Edward F. Moore also published a variation of the algorithm
in 1959, and for this reason it is also sometimes called the Bellman–Ford–Moore algorithm.
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


def bellman_ford(graph, start):
    res = [float('inf')] * (v + 1)
    res[start] = 0
    for _ in range(v - 1):
        for start in graph.keys():
            for end, weight in graph[start].items():
                res[end] = min(res[end], res[start] + weight)
    return res
