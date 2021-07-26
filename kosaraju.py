"""
In computer science, Kosaraju-Sharir's algorithm (also known as Kosaraju's algorithm) is a linear time algorithm 
to find the strongly connected components of a directed graph. Aho, Hopcroft and Ullman credit it to S. Rao Kosaraju 
and Micha Sharir. Kosaraju suggested it in 1978 but did not publish it, while Sharir independently discovered it and 
published it in 1981. It makes use of the fact that the transpose graph (the same graph with the direction of every 
edge reversed) has exactly the same strongly connected components as the original graph.
"""

import sys

v, e = map(int, sys.stdin.readline().split())

graph = [[] for _ in range(v + 1)]
reverse = [[] for _ in range(v + 1)]

for _ in range(e):
    a, b = map(int, sys.stdin.readline().split())
    graph[a].append(b)
    reverse[b].append(a)

stack = []
visit = [0] * (v + 1)
for i in range(1, v + 1):
    if visit[i] == 0:
        queue = [i]
        visit[i] = 1
        while queue:
            cur = queue[-1]
            for nxt in graph[cur]:
                if visit[nxt] == 0:
                    visit[nxt] = 1
                    queue.append(nxt)
                    break
            else:
                stack.append(queue.pop())

scc = []
finish = [0] * (v + 1)
while stack:
    node = stack.pop()
    if finish[node]:
        continue

    res = []
    finish[node] = 1
    queue = [node]
    while queue:
        cur = queue[-1]
        for nxt in reverse[cur]:
            if finish[nxt] == 0:
                finish[nxt] = 1
                queue.append(nxt)
                break
        else:
            res.append(queue.pop())

    scc.append(res)
