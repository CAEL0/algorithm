import sys
from math import log2, ceil
input = sys.stdin.readline

n = int(input())
arr = [*map(int, input().split())]
height = ceil(log2(n))
z = 2 ** height
tree = [[0] * 4 for _ in range(2 * z)]

for i in range(n):
    tree[2 ** height + i] = [arr[i]] * 4

for h in range(height - 1, -1, -1):
    for i in range(2 ** h, 2 ** (h + 1)):
        max1, left1, right1, sum1 = tree[2 * i]
        max2, left2, right2, sum2 = tree[2 * i + 1]
        tree[i] = (max(max1, max2, right1 + left2), max(left1, sum1 + left2), max(right2, right1 + sum2), sum1 + sum2)


def maximum(a, b):
    res1 = [-float('inf'), 0, -float('inf'), 0]
    res2 = [-float('inf'), -float('inf'), 0, 0]
    a += z - 1
    b += z - 1
    while a <= b:
        if a % 2:
            res1 = [max(res1[0], tree[a][0], res1[2] + tree[a][1]), max(res1[1], res1[3] + tree[a][1]), max(tree[a][2], res1[2] + tree[a][3]), res1[3] + tree[a][3]]
            a += 1
        if b % 2 == 0:
            res2 = [max(res2[0], tree[b][0], res2[1] + tree[b][2]), max(tree[b][1], res2[1] + tree[b][3]), max(res2[2], tree[b][2] + res2[3]), res2[3] + tree[b][3]]
            b -= 1
        a //= 2
        b //= 2

    return max(res1[0], res2[0], res1[2] + res2[1])


def update(k, c):
    idx = z + k - 1
    tree[idx] = [c] * 4
    while idx > 1:
        idx //= 2
        max1, left1, right1, sum1 = tree[2 * idx]
        max2, left2, right2, sum2 = tree[2 * idx + 1]
        tree[idx] = (max(max1, max2, right1 + left2), max(left1, sum1 + left2), max(right2, right1 + sum2), sum1 + sum2)
