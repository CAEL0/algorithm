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
    if not visit[i]:
        visit[i] = 1
        queue = [i]
        while queue:
            cur = queue[-1]
            for nxt in graph[cur]:
                if not visit[nxt]:
                    visit[nxt] = 1
                    queue.append(nxt)
                    break
            else:
                stack.append(queue.pop())

scc = []
finish = [0] * (v + 1)
while stack:
    node = stack.pop()
    if not finish[node]:
        finish[node] = 1
        res = []
        queue = [node]
        while queue:
            cur = queue[-1]
            for nxt in reverse[cur]:
                if not finish[nxt]:
                    finish[nxt] = 1
                    queue.append(nxt)
                    break
            else:
                res.append(queue.pop())
        scc.append(res)
