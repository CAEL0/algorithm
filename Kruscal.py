import sys

v, e = map(int, sys.stdin.readline().split())
graph = []
for _ in range(e):
    a, b, c = map(int, sys.stdin.readline().split())
    graph.append((c, a, b))

graph.sort()
parent = [i for i in range(v + 1)]


def union(x, y):
    parent_x = find(x)
    parent_y = find(y)
    parent[parent_x] = parent_y


def find(u):
    if u != parent[u]:
        parent[u] = find(parent[u])
    return parent[u]


def kruskal(graph):
    res = 0
    idx = 0
    for (c, a, b) in graph:
        if find(a) != find(b):
            union(a, b)
            res += c
            idx += 1

        if idx == v - 1:
            break

    return res


print(kruskal(graph))
