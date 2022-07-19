"""
In graph theory and computer science, the lowest common ancestor (LCA) (also called least common ancestor)
of two nodes v and w in a tree or directed acyclic graph (DAG) T is the lowest (i.e. deepest) node that has both v and w as descendants,
where we define each node to be a descendant of itself (so if v has a direct connection from w, w is the lowest common ancestor).
"""

# BOJ 11438 LCA 2

import sys
input = sys.stdin.readline

n = int(input())
graph = [[] for _ in range(n + 1)]
for _ in range(n - 1):
    a, b = map(int, input().split())
    graph[a].append(b)
    graph[b].append(a)

sparse = [[1] * (n + 1) for _ in range(20)]
queue = [(1, 2)]
depth = [1] * (n + 1)
visit = [0] * (n + 1)
visit[1] = 1
while queue:
    cur, d = queue.pop()
    for nxt in graph[cur]:
        if not visit[nxt]:
            depth[nxt] = d
            visit[nxt] = 1
            sparse[0][nxt] = cur
            queue.append((nxt, d + 1))

for i in range(19):
    for j in range(1, n + 1):
        sparse[i + 1][j] = sparse[i][sparse[i][j]]

for _ in range(int(input())):
    a, b = map(int, input().split())
    if depth[a] > depth[b]:
        a, b = b, a
    d = depth[b] - depth[a]
    for i in range(20):
        if d & (1 << i):
            b = sparse[i][b]
    
    if a == b:
        print(a)
        continue
    
    while True:
        for i in range(19, -1, -1):
            if sparse[i][a] != sparse[i][b]:
                a = sparse[i][a]
                b = sparse[i][b]
        
        if sparse[0][a] == sparse[0][b]:
            print(sparse[0][a])
            break
