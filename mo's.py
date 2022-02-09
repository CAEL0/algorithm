import sys

n = int(sys.stdin.readline())
arr = list(map(int, sys.stdin.readline().split()))
z = max(arr)
q = int(sys.stdin.readline())
query = []
for i in range(q):
    a, b = map(int, sys.stdin.readline().split())
    query.append((a, b, i))
query.sort(key=lambda x: (x[0] // 300, x[1]))

ans = [0] * q
res = [0] * (z + 1)
cnt = 0
left, right, idx = query[0]
for j in range(left - 1, right):
    cnt += (res[arr[j]] == 0)
    res[arr[j]] += 1
ans[idx] = cnt

for i in range(1, q):
    ll, rr, idx = query[i]
    if ll < left:
        for j in range(ll - 1, left - 1):
            cnt += (res[arr[j]] == 0)
            res[arr[j]] += 1
    else:
        for j in range(left - 1, ll - 1):
            res[arr[j]] -= 1
            cnt -= (res[arr[j]] == 0)
    if right < rr:
        for j in range(right, rr):
            cnt += (res[arr[j]] == 0)
            res[arr[j]] += 1
    else:
        for j in range(rr, right):
            res[arr[j]] -= 1
            cnt -= (res[arr[j]] == 0)
    ans[idx] = cnt
    left = ll
    right = rr
