# BOJ 1786 찾기

t = input()
p = input()
lps = [0] * len(p)
j = 0
for i in range(1, len(p)):
    while j and (p[i] != p[j]):
        j = lps[j - 1]
    if p[i] == p[j]:
        j += 1
        lps[i] = j

ans = []
j = 0
for i in range(len(t)):
    while j and (t[i] != p[j]):
        j = lps[j - 1]
    if t[i] == p[j]:
        if j == len(p) - 1:
            ans.append(i - len(p) + 2)
            j = lps[j]
        else:
            j += 1

print(*ans)
