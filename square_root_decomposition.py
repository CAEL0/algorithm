import sys
input = sys.stdin.readline

n, q = map(int, input().split())
k = int(n ** 0.5)
arr = [int(input()) for _ in range(n)]
group = [[float('inf'), -float('inf')] for _ in range(k + 2)]

for i in range(n):
    idx = i // k
    group[idx][0] = min(group[idx][0], arr[i])
    group[idx][1] = max(group[idx][1], arr[i])

for _ in range(q):
    a, b = map(lambda x: int(x) - 1, input().split())
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
input = sys.stdin.readline

n, m, o = map(int, input().split())
k = int(n ** 0.5)
arr = [int(input()) for _ in range(n)]
group = [0] * (k + 2)

for i in range(n):
    group[i // k] += arr[i]

for _ in range(m + o):
    a, b, c = map(int, input().split())
    if a == 1:
        b -= 1
        group[b // k] += c - arr[b]
        arr[b] = c
    else:
        b -= 1
        c -= 1
        ans = 0
        idx = b
        while idx <= c:
            if (idx % k == 0) and (idx + k - 1 <= c):
                ans += group[idx // k]
                idx += k
            else:
                ans += arr[idx]
                idx += 1
        
        print(ans)
