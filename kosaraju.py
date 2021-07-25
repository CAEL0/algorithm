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
inverse = [[] for _ in range(v + 1)]

for _ in range(e):
    a, b = map(int, sys.stdin.readline().split())
    graph[a].append(b)
    inverse[b].append(a)

scc = []
stack = []
visit1 = [0] * (v + 1)
for i in range(1, v + 1):
    if visit1[i] == 0:
        visit1[i] = 1
        queue = [i]
        while queue:
            tar = queue[-1]
            flag = True
            for nxt in graph[tar]:
                if visit1[nxt] == 0:
                    visit1[nxt] = 1
                    flag = False
                    queue.append(nxt)
            if flag:
                stack.append(queue.pop())

visit2 = [0] * (v + 1)
while stack:
    queue = [stack[-1]]
    visit2[stack[-1]] = 1
    while queue:
        tar = queue[-1]
        flag = True
        for nxt in inverse[tar]:
            if visit2[nxt] == 0:
                visit2[nxt] = 1
                flag = False
                queue.append(nxt)
        if flag:
            break

    scc.append(queue)
    for _ in range(len(queue)):
        stack.pop()

print(scc)
