# BOJ 9248 Suffix Array

import sys

s = sys.stdin.readline().strip()
n = len(s)
sa = [i for i in range(n)]
pos = [ord(s[i]) for i in range(n)] + [0]
d = 1
while True:
    sa.sort(key=lambda x: (pos[x], pos[min(x + d, n)]))
    tmp = [0] * n
    for i in range(n - 1):
        x, y = sa[i], sa[i + 1]
        tmp[i + 1] = tmp[i] + ((pos[x], pos[min(x + d, n)]) < (pos[y], pos[min(y + d, n)]))
    
    for i in range(n):
        pos[sa[i]] = tmp[i]
    
    if tmp[-1] == n - 1:
        break
    
    d *= 2

lcp = [0] * n
k = 0
for i in range(n):
    if pos[i] == 0:
        k -= (k > 0)
        continue
    
    j = sa[pos[i] - 1]
    while (max(i, j) + k < n) and (s[i + k] == s[j + k]):
        k += 1
    
    lcp[pos[i]] = k
    k -= (k > 0)

#--------------------------------------------------------------------------------

import sys

s = sys.stdin.readline().strip()
n = len(s)
sa = [i for i in range(n)]
pos = [ord(s[i]) for i in range(n)] + [0]
d = 1
while True:    
    cnt = [0] * max(n, 200)
    cnt[0] = d
    for i in range(d, n):
        cnt[pos[i]] += 1
    
    for i in range(1, len(cnt)):
        cnt[i] += cnt[i - 1]
    
    idx = [0] * n
    for i in range(n - 1, -1, -1):
        cnt[pos[min(i + d, n)]] -= 1
        idx[cnt[pos[min(i + d, n)]]] = i
    
    cnt = [0] * max(n, 200)
    for i in range(n):
        cnt[pos[i]] += 1
    
    for i in range(1, len(cnt)):
        cnt[i] += cnt[i - 1]
    
    for i in range(n - 1, -1, -1):
        cnt[pos[idx[i]]] -= 1
        sa[cnt[pos[idx[i]]]] = idx[i]
    
    tmp = [0] * n
    for i in range(n - 1):
        x, y = sa[i], sa[i + 1]
        tmp[i + 1] = tmp[i] + ((pos[x], pos[min(x + d, n)]) < (pos[y], pos[min(y + d, n)]))
    
    for i in range(n):
        pos[sa[i]] = tmp[i] + 1
    
    if tmp[-1] == n - 1:
        break
    
    d *= 2

lcp = [0] * n
k = 0
for i in range(n):
    if pos[i] == 1:
        k -= (k > 0)
        continue
    
    j = sa[pos[i] - 2]
    while (max(i, j) + k < n) and (s[i + k] == s[j + k]):
        k += 1
    
    lcp[pos[i] - 1] = k
    k -= (k > 0)
