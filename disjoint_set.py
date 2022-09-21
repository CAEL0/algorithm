# BOJ 1717 집합의 표현

import sys
input = sys.stdin.readline

n = int(input())
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
