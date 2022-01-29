import sys

n, q = map(int, sys.stdin.readline().split())
k = int(n ** 0.5)
arr = [int(sys.stdin.readline()) for _ in range(n)]
group = [[float('inf'), -float('inf')] for _ in range(k + 2)]

for i in range(n):
    idx = i // k
    group[idx][0] = min(group[idx][0], arr[i])
    group[idx][1] = max(group[idx][1], arr[i])

for _ in range(q):
    a, b = map(lambda x: int(x) - 1, sys.stdin.readline().split())
    idx1 = a // k
    idx2 = b // k
    ans = [float('inf'), -float('inf')]
    for i in range(idx1 + 1, idx2):
        ans[0] = min(ans[0], group[i][0])
        ans[1] = max(ans[1], group[i][1])
    
    for i in range(a, min(k * (idx1 + 1), b + 1)):
        ans[0] = min(ans[0], arr[i])
        ans[1] = max(ans[1], arr[i])
    
    for i in range(max(a, k * idx2), b + 1):
        ans[0] = min(ans[0], arr[i])
        ans[1] = max(ans[1], arr[i])
    
    print(*ans)

#--------------------------------------------------------------------------------

import sys

n, m, o = map(int, sys.stdin.readline().split())
k = int(n ** 0.5)
arr = [int(sys.stdin.readline()) for _ in range(n)]
group = [0] * (k + 2)

for i in range(n):
    idx = i // k
    group[idx] += arr[i]

for _ in range(m + o):
    a, b, c = map(int, sys.stdin.readline().split())
    if a == 1:
        b -= 1
        idx = b // k
        gap = c - arr[b]
        arr[b] = c
        group[idx] += gap
    else:
        b -= 1
        c -= 1
        idx1 = b // k
        idx2 = c // k
        ans = 0
        for i in range(idx1 + 1, idx2):
            ans += group[i]

        for i in range(b, min(k * (idx1 + 1), c + 1)):
            ans += arr[i]

        if idx1 != idx2:
            for i in range(max(b, k * idx2), c + 1):
                ans += arr[i]

        print(ans)
