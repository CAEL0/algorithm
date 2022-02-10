import sys

n = int(sys.stdin.readline())
arr = list(map(int, sys.stdin.readline().split()))
sparse = [[0] * (n + 1) for _ in range(20)]
for j in range(1, n + 1):
    sparse[0][j] = arr[j - 1]

for i in range(1, 20):
    for j in range(1, n + 1):
        sparse[i][j] = sparse[i - 1][sparse[i - 1][j]]

for _ in range(int(sys.stdin.readline())):
    n, x = map(int, sys.stdin.readline().split())
    for i in range(20):
        if n & (1 << i):
            x = sparse[i][x]
    print(x)
