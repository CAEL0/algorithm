import sys
from collections import deque

n, m = map(int, sys.stdin.readline().split())
a = list(map(int, sys.stdin.readline().split()))
b = list(map(int, sys.stdin.readline().split()))
board = [list(map(int, sys.stdin.readline().split())) for _ in range(m)]
graph = [[] for _ in range(m + n + 2)]

for i in range(1, m + 1):
    graph[0].append([i, b[i - 1]])
    for j in range(m + 1, m + n + 1):
        graph[i].append([j, float('inf')])

for j in range(m + 1, m + n + 1):
    graph[j].append([m + n + 1, a[j - m - 1]])

weight = 0
while True:
    res = [float('inf')] * (m + n + 2)
    res[0] = 0

    prev = [-1] * (m + n + 2)
    visit = [0] * (m + n + 2)
    queue = deque([0])

    while queue:
        cur = queue.popleft()
        visit[cur] = 0
        
        for nxt, capacity in graph[cur]:
            if 0 < cur < nxt < m + n + 1:
                cost = board[cur - 1][nxt - m - 1]
            elif 0 < nxt < cur < m + n + 1:
                cost = -board[nxt - 1][cur - m - 1]
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

    flow = float('inf')
    nxt = m + n + 1
    while nxt:
        cur = prev[nxt]
        for i in range(len(graph[cur])):
            if graph[cur][i][0] == nxt:
                flow = min(flow, graph[cur][i][1])
                break
        nxt = cur
    
    nxt = m + n + 1
    while nxt:
        cur = prev[nxt]

        if 0 < cur < nxt < m + n + 1:
            weight += flow * board[cur - 1][nxt - m - 1]
        elif 0 < nxt < cur < m + n + 1:
            weight -= flow * board[nxt - 1][cur - m - 1]
        
        for i in range(len(graph[cur])):
            if graph[cur][i][0] == nxt:
                graph[cur][i][1] -= flow
                if graph[cur][i][1] == 0:
                    graph[cur].remove([nxt, 0])
                break
        
        for i in range(len(graph[nxt])):
            if graph[nxt][i][0] == cur:
                graph[nxt][i][1] += flow
                break
        else:
            graph[nxt].append([cur, flow])
        nxt = cur
    
print(weight)
