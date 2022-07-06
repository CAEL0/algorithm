"""
In computer science, 2-satisfiability, 2-SAT or just 2SAT is a computational problem of assigning values to variables,
each of which has two possible values, in order to satisfy a system of constraints on pairs of variables.
It is a special case of the general Boolean satisfiability problem, which can involve constraints on more than two variables,
and of constraint satisfaction problems, which can allow more than two choices for the value of each variable.
But in contrast to those more general problems, which are NP-complete, 2-satisfiability can be solved in polynomial time.
"""

# BOJ 11281 2-SAT - 4

import sys
input = sys.stdin.readline

n, m = map(int, input().split())
graph = [[] for _ in range(2 * n + 1)]

for _ in range(m):
    a, b = map(int, input().split())
    graph[-a].append(b)
    graph[-b].append(a)

stack = []
scc_num = 1
scc_idx = [0] * (2 * n + 1)
finish = [0] * (2 * n + 1)
visit = [0] * (2 * n + 1)
idx = 1


def dfs(cur):
    global idx, scc_num
    visit[cur] = idx
    low = idx
    idx += 1
    stack.append(cur)

    for nxt in graph[cur]:
        if not visit[nxt]:
            low = min(low, dfs(nxt))
        elif not finish[nxt]:
            low = min(low, visit[nxt])

    if low == visit[cur]:
        while stack:
            top = stack.pop()
            finish[top] = 1
            scc_idx[top] = scc_num
            if cur == top:
                break
        scc_num += 1
    return low


for i in range(1, 2 * n + 1):
    if not visit[i]:
        dfs(i)

res = [0] * n
for i in range(1, n + 1):
    if scc_idx[i] == scc_idx[-i]:
        print(0)
        break
    if scc_idx[i] < scc_idx[-i]:
        res[i - 1] = 1
else:
    print(1)
    print(*res)

----------------------------------------------------------------------------------------------------

n, m = map(int, input().split())

graph = [[] for _ in range(2 * n + 1)]
reverse = [[] for _ in range(2 * n + 1)]

for _ in range(m):
    a, b = map(int, input().split())
    graph[-a].append(b)
    graph[-b].append(a)
    reverse[b].append(-a)
    reverse[a].append(-b)

stack = []
visit = [0] * (2 * n + 1)
for i in range(1, 2 * n + 1):
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

scc_num = 0
scc_idx = [0] * (2 * n + 1)
finish = [0] * (2 * n + 1)
while stack:
    node = stack.pop()
    if not finish[node]:
        finish[node] = 1
        queue = [node]
        while queue:
            cur = queue[-1]
            for nxt in reverse[cur]:
                if not finish[nxt]:
                    finish[nxt] = 1
                    queue.append(nxt)
                    break
            else:
                scc_idx[queue.pop()] = scc_num

        scc_num += 1

res = [0] * n
for i in range(1, n + 1):
    if scc_idx[i] == scc_idx[-i]:
        print(0)
        break
    if scc_idx[i] > scc_idx[-i]:
        res[i - 1] = 1
else:
    print(1)
    print(*res)
