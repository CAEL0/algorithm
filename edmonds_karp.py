"""
In computer science, the Edmonds–Karp algorithm is an implementation of the Ford–Fulkerson method for computing the maximum flow in a flow network in O(V * E ** 2) time.
The algorithm was first published by Yefim Dinitz (whose name is also transliterated "E. A. Dinic", notably as author of his early papers) in 1970
and independently published by Jack Edmonds and Richard Karp in 1972.
Dinic's algorithm includes additional techniques that reduce the running time to O(V ** 2 * E).
"""

import sys

n, m = map(int, sys.stdin.readline().split())
graph = [[0] * (n + 1) for _ in range(n + 1)]

for _ in range(m):
    start, end, capacity = map(int, sys.stdin.readline().split())
    graph[start][end] += capacity

ans = 0
while True:
    prev = [-1] * (n + 1)
    visit = [0] * (n + 1)
    queue = [(1, float('inf'))]
    while queue:
        cur, res = queue.pop()
        visit[cur] = 1
        for nxt in range(2, n + 1):
            if (nxt == n) and graph[cur][n]:
                res = min(res, graph[cur][n])
                prev[n] = cur
                break

            if not visit[nxt] and graph[cur][nxt]:
                prev[nxt] = cur
                queue.append((nxt, min(res, graph[cur][nxt])))

        if prev[n] != -1:
            break
    
    if prev[n] == -1:
        break

    ans += res
    nxt = n
    while True:
        cur = prev[nxt]
        graph[cur][nxt] -= res
        graph[nxt][cur] += res
        nxt = cur
        if nxt == 1:
            break

print(ans)
