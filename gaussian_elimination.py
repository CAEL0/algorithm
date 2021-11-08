"""
In mathematics, Gaussian elimination, also known as row reduction, is an algorithm for solving systems of linear equations.
It consists of a sequence of operations performed on the corresponding matrix of coefficients.
This method can also be used to compute the rank of a matrix, the determinant of a square matrix, and the inverse of an invertible matrix.
"""

import sys
from math import gcd


def lcm(*args):
    res = args[0] * args[1] // gcd(args[0], args[1])
    for i in range(2, len(args)):
        res = (res * args[i]) // gcd(res, args[i])
    return res


n = int(sys.stdin.readline())
equation = [list(map(int, sys.stdin.readline().split())) for _ in range(n)]

for z in range(n - 1):
    l = lcm(*[equation[i][z] for i in range(n - z)])

    for i in range(n - z):
        k = l // equation[i][z]
        for j in range(z, n + 1):
            equation[i][j] *= k

    for i in range(n - z - 1):
        for j in range(z, n + 1):
            equation[i][j] -= equation[- z - 1][j]

ans = []
for z in range(n):
    x = equation[z][-1] // equation[z][- z - 2]
    ans.append(x)

    for i in range(z + 1, n):
        equation[i][-1] -= x * equation[i][- z - 2]

print(*reversed(ans))
