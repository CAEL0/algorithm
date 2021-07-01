import sys

v, e = map(int, sys.stdin.readline().split())  # v : the number of vertices, e : the number of edges
graph = []
for _ in range(e):
    start, end, weight = map(int, sys.stdin.readline().split())  # start node -- weight -- end node
    graph.append((weight, start, end))

graph.sort()
parent = [i for i in range(v + 1)]


def union(x, y):
    parent[find(x)] = find(y)


def find(z):
    if z != parent[z]:
        parent[z] = find(parent[z])
    return parent[z]


def kruskal(graph):
	res = 0
	idx = 0
	for (weight, start, end) in graph:
		if find(start) != find(end):
			union(start, end)
			res += weight
			idx += 1
        
		if idx == v - 1:
			break

	return res


print(kruskal(graph))
