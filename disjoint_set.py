"""
In computer science, a disjoint-set data structure, also called a union–find data structure or merge–find set,
is a data structure that stores a collection of disjoint (non-overlapping) sets.
Equivalently, it stores a partition of a set into disjoint subsets.
It provides operations for adding new sets, merging sets (replacing them by their union), and finding a representative member of a set.
The last operation allows to find out efficiently if any two elements are in the same or different sets.
"""

import sys

n = int(sys.stdin.readline())
parent = [i for i in range(n + 1)]


def union(x, y):
    u, v = sorted((find(x), find(y)))
    parent[u] = v


def find(c):
    u = c
    v = parent[u]
    while u != v:
        u, v = v, parent[v]
    parent[c] = v
    return v
