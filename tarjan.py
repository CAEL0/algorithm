"""
Tarjan's strongly connected components algorithm is an algorithm in graph theory for finding the strongly 
connected components (SCCs) of a directed graph. It runs in linear time, matching the time bound for alternative 
methods including Kosaraju's algorithm and the path-based strong component algorithm. The algorithm is named for its 
inventor, Robert Tarjan.
"""

import sys
sys.setrecursionlimit(10 ** 5)

n, m = map(int, sys.stdin.readline().split())
graph = [[] for _ in range(n + 1)]

for _ in range(m):
    a, b = map(int, sys.stdin.readline().split())
    graph[a].append(b)

scc = []
stack = []
finish = [0] * (n + 1)
visit = [0] * (n + 1)
idx = 1


def dfs(cur):
    global idx
    visit[cur] = idx
    low = idx
    idx += 1
    stack.append(cur)

    for nxt in graph[cur]:
        if not visit[nxt]:
            low = min(low, dfs(nxt))
        elif not finish[nxt]:
            low = min(low, visit[nxt])

    if low == visit[cur]:
        res = []
        while stack:
            top = stack.pop()
            finish[top] = 1
            res.append(top)
            if cur == top:
                break
        scc.append(res)

    return low


for i in range(1, n + 1):
    if not visit[i]:
        dfs(i)
