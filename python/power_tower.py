# BOJ 13970 Power towers

import sys
input = sys.stdin.readline


def phi(x):
    res = x
    for i in range(2, int(x ** 0.5) + 2):
        if x % i == 0:
            res = res * (i - 1) // i
            while x % i == 0:
                x //= i
    
    if x > 1:
        res = res * (x - 1) // x
    return res


def solve(arr, idx, mod):
    phi_mod = phi(mod)
    if idx == len(arr) - 1:
        if arr[idx] > 100:
            return arr[idx] % mod
        return arr[idx]
    
    if idx == len(arr) - 2:
        if arr[-1] > 100:
            return pow(arr[idx], arr[idx + 1] % phi_mod + 100 * phi_mod, mod)
        return pow(arr[idx], arr[idx + 1], mod)
    
    if mod == 1:
        return 0
    return pow(arr[idx], solve(arr, idx + 1, phi_mod) + 100 * phi_mod, mod)


t, m = map(int, input().split())
for _ in range(t):
    line = [*map(int, input().split())]
    arr = []
    for i in range(1, len(line)):
        if line[i] == 1:
            break
        arr.append(line[i])
    
    while len(arr) > 1:
        res = 1
        for _ in range(arr[-1]):
            res *= arr[-2]
            if res > 100:
                break
        else:
            arr.pop()
            arr.pop()
            arr.append(res)
            continue
        break
    
    if not arr:
        print(1)
    else:
        print(solve(arr, 0, m) % m)
