import sys
input = sys.stdin.readline


def dfs(cur, res):
    if cur == n:
        return res
    
    for nxt in range(2, n + 1):
        if graph[cur][nxt] and not visit[nxt]:
            visit[nxt] = 1
            bottleneck = dfs(nxt, min(res, graph[cur][nxt]))
            if bottleneck:
                graph[cur][nxt] -= bottleneck
                graph[nxt][cur] += bottleneck
                return bottleneck
    return 0


n, m = map(int, input().split())
graph = [[0] * (n + 1) for _ in range(n + 1)]

for _ in range(m):
    start, end, capacity = map(int, input().split())
    graph[start][end] += capacity

ans = 0
flow = 1
while flow:
    visit = [0] * (n + 1)
    flow = dfs(1, float('inf'))
    ans += flow

print(ans)
