"""
The Euler tour technique (ETT), named after Leonhard Euler, is a method in graph theory for representing trees.
The tree is viewed as a directed graph that contains two directed edges for each edge in the tree.
The tree can then be represented as a Eulerian circuit of the directed graph, known as the Euler tour representation (ETR) of the tree.
The ETT allows for efficient, parallel computation of solutions to common problems in algorithmic graph theory.
It was introduced by Tarjan and Vishkin in 1984.
"""

# BOJ 14287 회사 문화 3

import sys
from math import log2, ceil
input = sys.stdin.readline

n, m = map(int, input().split())
num = [*map(int, input().split())]
graph = [[] for _ in range(n + 1)]
for i in range(1, n):
    graph[num[i]].append(i + 1)

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
height = ceil(log2(n))
tree = [0] * 2 ** (height + 1)


def partial_sum(a, b):
    res = 0
    a += 2 ** height - 1
    b += 2 ** height - 1
    while a <= b:
        if a % 2:
            res += tree[a]
            a += 1
        if b % 2 == 0:
            res += tree[b]
            b -= 1
        a //= 2
        b //= 2
    return res


def change(k, c):
    idx = 2 ** height + k - 1
    while idx >= 1:
        tree[idx] += c
        idx //= 2


for _ in range(m):
    query = [*map(int, input().split())]
    if query[0] == 1:
        change(dfs_in[query[1]], query[2])
    else:
        print(partial_sum(dfs_in[query[1]], dfs_out[query[1]]))
