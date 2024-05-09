import sys
input = sys.stdin.readline

n, m = map(int, input().split())
graph = [[] for _ in range(n + 1)]
for _ in range(m):
    a, b = map(int, input().split())
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
