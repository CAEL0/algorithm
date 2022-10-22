import sys
from collections import defaultdict
input = sys.stdin.readline

v, e = map(int, input().split())
graph = defaultdict(dict)

for _ in range(e):
    a, b, c = map(int, input().split())
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
