# BOJ 15106 Fear Factoring

import sys
input = sys.stdin.readline


def f(n):
    ret = 0
    s = 1
    e = 1
    
    while True:
        a = n // s
        ret += (e - s + 1) * a * (e + s) // 2
        
        if a <= 1:
            break
        
        s = e + 1
        e = n // (n // s)
    
    return ret


a, b = map(int, input().split())
print(f(b) - f(a - 1))
