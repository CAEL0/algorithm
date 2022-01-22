"""
The Euler tour technique (ETT), named after Leonhard Euler, is a method in graph theory for representing trees.
The tree is viewed as a directed graph that contains two directed edges for each edge in the tree.
The tree can then be represented as a Eulerian circuit of the directed graph, known as the Euler tour representation (ETR) of the tree.
The ETT allows for efficient, parallel computation of solutions to common problems in algorithmic graph theory.
It was introduced by Tarjan and Vishkin in 1984.
"""

import sys

n = int(sys.stdin.readline())
arr = list(map(int, sys.stdin.readline().split()))
graph = [[] for _ in range(n + 1)]
for i in range(1, n):
    graph[arr[i]].append(i + 1)

dfn = 0
dfs_in = [0] * (n + 1)
dfs_out = [0] * (n + 1)


def dfs(cur):
    global dfn
    dfn += 1
    dfs_in[cur] = dfn
    for pos in graph[cur]:
        dfs(pos)

    dfs_out[cur] = dfn


dfs(1)
