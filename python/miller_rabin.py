# BOJ 5615 아파트 임대

import sys
input = sys.stdin.readline


def miller_rabin(x):
    if x == 1:
        return False

    s = 0
    d = x - 1
    while not (d & 1):
        s += 1
        d >>= 1

    for a in [2, 7, 61]:
        if a >= x - 1:
            break

        b = pow(a, d, x)
        if b in [1, x - 1]:
            continue

        if s == 1:
            return False
        
        for _ in range(s - 1):
            b = b * b % x
            if b == x - 1:
                break
        else:
            return False
    return True


ans = 0
for _ in range(int(input())):
    ans += miller_rabin(2 * int(input()) + 1)

print(ans)
