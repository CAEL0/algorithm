# BOJ 13275 가장 긴 팰린드롬 부분 문자열


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
        
        while True:
            a[i] += 1
            if (i - a[i] == -1) or (i + a[i] == m):
                a[i] -= 1
                break
            
            if s[i - a[i]] != s[i + a[i]]:
                a[i] -= 1
                break
    return max(a)


s = input()
print(manacher('#' + '#'.join(s) + '#'))
