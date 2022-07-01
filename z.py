import sys
input = sys.stdin.readline


def z(s):
    m = len(s)
    res = [0] * m
    l = r = 0
    for i in range(1, m):
        if i <= r:
            res[i] = min(r - i, res[i - l])
        
        while (i + res[i] < m) and (s[res[i]] == s[i + res[i]]):
            res[i] += 1
        
        if r < i + res[i] - 1:
            l = i
            r = i + res[i] - 1
    
    return res


s = input().rstrip()
res = z(s)
