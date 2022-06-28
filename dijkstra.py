"""
Dijkstra's algorithm is an algorithm for finding the shortest paths between nodes in a graph, which may represent, for example, road networks.
It was conceived by computer scientist Edsger W. Dijkstra in 1956 and published three years later. The algorithm exists in many variants.
Dijkstra's original algorithm found the shortest path between two given nodes, but a more common variant fixes a single node as the "source" node
and finds shortest paths from the source to all other nodes in the graph, producing a shortest-path tree.
"""

# BOJ 1753 최단경로

import sys
from heapq import heappush, heappop

v, e = map(int, sys.stdin.readline().split())
graph = [[] for _ in range(v + 1)]

for _ in range(e):
    a, b, c = map(int, sys.stdin.readline().split())
    graph[a].append((b, c))


def dijkstra(graph, start):
    res = [float('inf')] * (v + 1)
    res[start] = 0
    queue = [(0, start)]
    while queue:
        old_weight, old_node = heappop(queue)
        if res[old_node] == old_weight:
            for new_node, new_weight in graph[old_node]:
                total_weight = old_weight + new_weight
                if total_weight < res[new_node]:
                    res[new_node] = total_weight
                    heappush(queue, (total_weight, new_node))
    return res
