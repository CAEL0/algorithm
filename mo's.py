# BOJ 13547 수열과 쿼리 5

import sys

n = int(sys.stdin.readline())
arr = list(map(int, sys.stdin.readline().split()))
q = int(sys.stdin.readline())
query = []
for i in range(q):
    a, b = map(int, sys.stdin.readline().split())
    query.append((a, b, i))
query.sort(key=lambda x: (x[0] // 300, x[1]))


def add(l, r):
    global cnt
    for j in range(l, r):
        cnt += (res[arr[j]] == 0)
        res[arr[j]] += 1


def sub(l, r):
    global cnt
    for j in range(l, r):
        res[arr[j]] -= 1
        cnt -= (res[arr[j]] == 0)


ans = [0] * q
res = [0] * (max(arr) + 1)
cnt = 0
left, right, idx = query[0]
add(left - 1, right)
ans[idx] = cnt

for i in range(1, q):
    ll, rr, idx = query[i]
    if ll < left:
        add(ll - 1, left - 1)
    else:
        sub(left - 1, ll - 1)
    if right < rr:
        add(right, rr)
    else:
        sub(rr, right)
    ans[idx] = cnt
    left = ll
    right = rr
