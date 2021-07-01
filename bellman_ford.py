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

V, E = map(int, sys.stdin.readline().split())  # V : the number of vertices, E : the number of edges


def bellman_ford(graph: defaultdict, start: int, step=V-1) -> list:
    res = [float('inf') for _ in range(V + 1)]
    res[start] = 0
    for _ in range(step):
        for start in graph.keys():
            for end, weight in graph[start].items():
                res[end] = min(res[end], res[start] + weight)
    return res
