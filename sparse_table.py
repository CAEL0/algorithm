import sys

# BOJ 17435 합성함수와 쿼리

n = int(sys.stdin.readline())
arr = list(map(int, sys.stdin.readline().split()))
sparse = [[0] * (n + 1) for _ in range(20)]
for j in range(n):
    sparse[0][j + 1] = arr[j]

for i in range(19):
    for j in range(1, n + 1):
        sparse[i + 1][j] = sparse[i][sparse[i][j]]

for _ in range(int(sys.stdin.readline())):
    m, x = map(int, sys.stdin.readline().split())
    for i in range(20):
        if m & (1 << i):
            x = sparse[i][x]
    print(x)
