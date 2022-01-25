import sys
from bisect import bisect
from math import log2, ceil


def merge(k, l, r):
    i = j = 0
    while True:
        if i == len(tree[l]):
            tree[k].extend(tree[r][j:])
            return

        if j == len(tree[r]):
            tree[k].extend(tree[l][i:])
            return

        if tree[l][i] <= tree[r][j]:
            tree[k].append(tree[l][i])
            i += 1
        else:
            tree[k].append(tree[r][j])
            j += 1


n = int(sys.stdin.readline())
arr = list(map(int, sys.stdin.readline().split()))
height = ceil(log2(n))
z = 2 ** height
tree = [[] for _ in range(2 * z)]

for i in range(n):
    tree[z + i] = [arr[i]]

for h in range(height - 1, -1, -1):
    for i in range(2 ** h, 2 ** (h + 1)):
        merge(i, 2 * i, 2 * i + 1)


def larger(a, b, k):
    res = 0
    a += z - 1
    b += z - 1
    while a <= b:
        if a % 2:
            res += len(tree[a]) - bisect(tree[a], k)
            a += 1
        if b % 2 == 0:
            res += len(tree[b]) - bisect(tree[b], k)
            b -= 1
        a //= 2
        b //= 2
    return res


for _ in range(int(sys.stdin.readline())):
    print(larger(*map(int, sys.stdin.readline().split())))
