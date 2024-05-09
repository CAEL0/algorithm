# BOJ 11281 2-SAT - 4

import sys
input = sys.stdin.readline
sys.setrecursionlimit(10 ** 4)

n, m = map(int, input().split())
grp = [[] for _ in range(2 * n + 1)]

for _ in range(m):
    a, b = map(int, input().split())
    grp[-a].append(b)
    grp[-b].append(a)

idx = 1
scc_num = 1
stk = []
vst = [0] * (2 * n + 1)
scc_idx = [0] * (2 * n + 1)
finish = [0] * (2 * n + 1)


def dfs(cur):
    global idx, scc_num
    vst[cur] = idx
    low = idx
    idx += 1
    stk.append(cur)

    for nxt in grp[cur]:
        if not vst[nxt]:
            low = min(low, dfs(nxt))
        elif not finish[nxt]:
            low = min(low, vst[nxt])

    if low == vst[cur]:
        while stk:
            top = stk.pop()
            finish[top] = 1
            scc_idx[top] = scc_num
            if cur == top:
                break
        scc_num += 1
    return low


for i in range(1, 2 * n + 1):
    if not vst[i]:
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
grp = [[] for _ in range(2 * n + 1)]
rvs = [[] for _ in range(2 * n + 1)]

for _ in range(m):
    a, b = map(int, input().split())
    grp[-a].append(b)
    grp[-b].append(a)
    rvs[b].append(-a)
    rvs[a].append(-b)

stk = []
vst = [0] * (2 * n + 1)
for i in range(1, 2 * n + 1):
    if not vst[i]:
        vst[i] = 1
        que = [i]
        while que:
            cur = que[-1]
            for nxt in grp[cur]:
                if not vst[nxt]:
                    vst[nxt] = 1
                    que.append(nxt)
                    break
            else:
                stk.append(que.pop())

scc_num = 0
scc_idx = [0] * (2 * n + 1)
finish = [0] * (2 * n + 1)
while stk:
    node = stk.pop()
    if not finish[node]:
        finish[node] = 1
        que = [node]
        while que:
            cur = que[-1]
            for nxt in rvs[cur]:
                if not finish[nxt]:
                    finish[nxt] = 1
                    que.append(nxt)
                    break
            else:
                scc_idx[que.pop()] = scc_num
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
