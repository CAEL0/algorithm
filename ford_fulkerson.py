"""
The Ford–Fulkerson method or Ford–Fulkerson algorithm (FFA) is a greedy algorithm that computes the maximum flow in a flow network.
It is sometimes called a "method" instead of an "algorithm" as the approach to finding augmenting paths in a residual graph is not fully specified 
or it is specified in several implementations with different running times. It was published in 1956 by L. R. Ford Jr. and D. R. Fulkerson.
The name "Ford–Fulkerson" is often also used for the Edmonds–Karp algorithm, which is a fully defined implementation of the Ford–Fulkerson method.
"""

import sys


def dfs(cur, res):
    if cur == n:
        return res
    
    for nxt in range(1, n + 1):
        if graph[cur][nxt] and not visit[nxt]:
            visit[nxt] = 1
            bottleneck = dfs(nxt, min(res, graph[cur][nxt]))
            if bottleneck:
                graph[cur][nxt] -= bottleneck
                graph[nxt][cur] += bottleneck
                return bottleneck
    
    return 0


n, m = map(int, sys.stdin.readline().split())
graph = [[0] * (n + 1) for _ in range(n + 1)]

for _ in range(m):
    start, end, capacity = map(int, sys.stdin.readline().split())
    graph[start][end] += capacity

ans = 0
flow = 1
while flow:
    visit = [0] * (n + 1)
    flow = dfs(1, float('inf'))
    ans += flow

print(ans)
