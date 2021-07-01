'''
In computer science, Prim's (also known as Jarník's) algorithm is a greedy algorithm that finds a minimum spanning tree for a weighted undirected graph. This means it finds a subset of the edges that forms a tree that includes every vertex, where the total weight of all the edges in the tree is minimized. The algorithm operates by building this tree one vertex at a time, from an arbitrary starting vertex, at each step adding the cheapest possible connection from the tree to another vertex.
'''


import sys
import heapq
from collections import defaultdict

v, e = map(int, sys.stdin.readline().split())
visit = [0] * (v + 1)
graph = defaultdict(list)
for _ in range(e):
	a, b, c = map(int, sys.stdin.readline().split())
	graph[a].append((c, b))
	graph[b].append((c, a))


def prim(graph):
	res = 0
	adj = []
	new = 1
	visit[1] = 1
	for _ in range(v - 1):
		for (weight, node) in graph[new]:
			if visit[node] == 0:
				heapq.heappush(adj, (weight, node))

		while True:
			(weight, new) = heapq.heappop(adj)
			if visit[new] == 0:
				visit[new] = 1
				res += weight
				break

	return res


print(prim(graph))
