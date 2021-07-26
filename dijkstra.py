"""
Dijkstra's algorithm is an algorithm for finding the shortest paths between nodes in a graph, which may represent, 
for example, road networks. It was conceived by computer scientist Edsger W. Dijkstra in 1956 and published three 
years later. The algorithm exists in many variants. Dijkstra's original algorithm found the shortest path between two 
given nodes,[6] but a more common variant fixes a single node as the "source" node and finds shortest paths from the 
source to all other nodes in the graph, producing a shortest-path tree.
"""

import sys
from heapq import heappush, heappop
from collections import defaultdict

v, e = map(int, sys.stdin.readline().split())


def dijkstra(graph: defaultdict, start: int) -> dict:
    res = {node: float('inf') for node in range(1, v + 1)}
    res[start] = 0
    queue = [[0, start]]

    while queue:
        old_weight, old_node = heappop(queue)
        if res[old_node] < old_weight:
            continue

        for new_node, new_weight in graph[old_node].items():
            total_weight = old_weight + new_weight
            if total_weight < res[new_node]:
                res[new_node] = total_weight
                heappush(queue, [total_weight, new_node])

    return res
