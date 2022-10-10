import sys
from collections import deque

n, m = map(int, sys.stdin.readline().split())
graph = [[] for _ in range(n + 1)]
for _ in range(m):
    a, b, t = map(int, sys.stdin.readline().split())
    graph[a].append((b, t))

res = [float('inf')] * (n + 1)
visit = [0] * (n + 1)

res[1] = 0
queue = deque([1])
while queue:
    cur = queue.popleft()
    visit[cur] = 0
    for nxt, weight in graph[cur]:
        if res[nxt] > res[cur] + weight:
            res[nxt] = res[cur] + weight
            if not visit[nxt]:
                queue.append(nxt)
                visit[nxt] = 1
