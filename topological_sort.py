"""
In computer science, a topological sort or topological ordering of a directed graph is a linear ordering of its vertices
such that for every directed edge uv from vertex u to vertex v, u comes before v in the ordering.
For instance, the vertices of the graph may represent tasks to be performed, and the edges may represent constraints that one task must be performed before another;
in this application, a topological ordering is just a valid sequence for the tasks.
A topological ordering is possible if and only if the graph has no directed cycles, that is, if it is a directed acyclic graph (DAG).
Any DAG has at least one topological ordering, and algorithms are known for constructing a topological ordering of any DAG in linear time.
Topological sorting has many applications especially in ranking problems such as feedback arc set.
"""

import sys
from collections import deque
input = sys.stdin.readline

N, M = map(int, input().split())
G = [[] for _ in range(N + 1)]
ind = [0] * (N + 1)
for _ in range(M):
    a, b = map(int, input().split())
    G[a].append(b)
    ind[b] += 1

queue = deque([i for i in range(1, N + 1) if ind[i] == 0])
while queue:
    i = queue.popleft()
    print(i)
    for j in G[i]:
        ind[j] -= 1
        if ind[j] == 0:
            queue.append(j)
