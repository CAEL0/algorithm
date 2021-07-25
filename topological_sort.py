"""
In computer science, a topological sort or topological ordering of a directed graph is a linear ordering of its 
vertices such that for every directed edge uv from vertex u to vertex v, u comes before v in the ordering. For 
instance, the vertices of the graph may represent tasks to be performed, and the edges may represent constraints that 
one task must be performed before another; in this application, a topological ordering is just a valid sequence for 
the tasks. A topological ordering is possible if and only if the graph has no directed cycles, that is, if it is a 
directed acyclic graph (DAG). Any DAG has at least one topological ordering, and algorithms are known for 
constructing a topological ordering of any DAG in linear time. Topological sorting has many applications especially 
in ranking problems such as feedback arc set.
"""

import sys
from collections import deque

n, m = map(int, sys.stdin.readline().split())
child = [[] for _ in range(n + 1)]
parent = [[] for _ in range(n + 1)]
for _ in range(m):
    a, b = map(int, sys.stdin.readline().split())
    child[a].append(b)
    parent[b].append(a)

res = []
queue = deque()
for i in range(1, n + 1):
    if not parent[i]:
        queue.append(i)

while queue:
    i = queue.popleft()
    res.append(j)

    for j in child[i]:
        parent[j].remove(i)
        if not parent[j]:
            queue.append(j)

print(*res)
