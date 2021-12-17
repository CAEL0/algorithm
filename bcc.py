"""
In graph theory, a biconnected component (sometimes known as a 2-connected component) is a maximal biconnected subgraph.
Any connected graph decomposes into a tree of biconnected components called the block-cut tree of the graph.
The blocks are attached to each other at shared vertices called cut vertices or separating vertices or articulation points.
Specifically, a cut vertex is any vertex whose removal increases the number of connected components.
"""

import sys

n, m = map(int, sys.stdin.readline().split())
graph = [[] for _ in range(n + 1)]
for _ in range(m):
    a, b = map(int, sys.stdin.readline().split())
    graph[a].append(b)
    graph[b].append(a)


def dfs(cur, parent):
    global idx
    dfsn[cur] = idx
    low = idx
    idx += 1

    for nxt in graph[cur]:
        if nxt == parent:
            continue

        if not dfsn[nxt]:
            stack.append((cur, nxt))
            child = dfs(nxt, cur)
            low = min(low, child)

            if dfsn[cur] <= child:
                res = []
                while stack[-1] != (cur, nxt):
                    res.append(stack.pop())
                res.append(stack.pop())
                bcc.append(res)
            
        elif low > dfsn[nxt]:
            low = min(low, dfsn[nxt])
            stack.append((cur, nxt))
    return low


bcc = []
stack = []
dfsn = [0] * (n + 1)
idx = 1

for i in range(1, n + 1):
    if not dfsn[i]:
        dfs(i, -1)
