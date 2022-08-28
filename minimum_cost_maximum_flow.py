# BOJ 11408 열혈강호 5

import sys
from collections import deque

n, m = map(int, sys.stdin.readline().split())
board = [[0] * (m + 1) for _ in range(n + 1)]
graph = [[] for _ in range(n + m + 2)]

for i in range(1, n + 1):
    data = list(map(int, sys.stdin.readline().split()))
    for j in range(data[0]):
        board[i][data[2 * j + 1]] = data[2 * j + 2]
        graph[i].append(data[2 * j + 1] + n)

for i in range(1, n + 1):
    graph[0].append(i)

for j in range(n + 1, n + m + 1):
    graph[j].append(n + m + 1)

ans = 0
weight = 0
while True:
    res = [float('inf')] * (n + m + 2)
    res[0] = 0

    prev = [-1] * (n + m + 2)
    visit = [0] * (n + m + 2)
    queue = deque([0])

    while queue:
        cur = queue.popleft()
        visit[cur] = 0
        
        for nxt in graph[cur]:
            if 0 < cur < nxt < n + m + 1:
                cost = board[cur][nxt - n]
            elif 0 < nxt < cur < n + m + 1:
                cost = -board[nxt][cur - n]
            else:
                cost = 0
            
            if res[nxt] > res[cur] + cost:
                res[nxt] = res[cur] + cost
                prev[nxt] = cur

                if not visit[nxt]:
                    queue.append(nxt)
                    visit[nxt] = 1
    
    if res[-1] == float('inf'):
        break

    ans += 1
    nxt = n + m + 1
    while nxt:
        cur = prev[nxt]
        
        if 0 < cur < nxt < n + m + 1:
            weight += board[cur][nxt - n]
        elif 0 < nxt < cur < n + m + 1:
            weight -= board[nxt][cur - n]
        
        graph[cur].remove(nxt)
        graph[nxt].append(cur)
        nxt = cur

print(ans)
print(weight)
