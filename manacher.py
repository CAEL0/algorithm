# BOJ 13275 가장 긴 팰린드롬 부분 문자열

import sys
input = sys.stdin.readline


def manacher(s):
    m = len(s)
    a = [0] * m
    r = c = -1
    for i in range(1, m):
        if r < i - 1 + a[i - 1]:
            r = i - 1 + a[i - 1]
            c = i - 1
        
        if r >= i:
            a[i] = min(r - i, a[2 * c - i])
        
        while (i - a[i] > 0) and (i + a[i] < m - 1) and (s[i - a[i] - 1] == s[i + a[i] + 1]):
            a[i] += 1
    
    return max(a)


s = input().rstrip()
print(manacher('#' + '#'.join(s) + '#'))
