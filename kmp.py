'''
In computer science, the Knuth–Morris–Pratt string-searching algorithm (or KMP algorithm) searches for occurrences of a "word" W within a main "text string" S
by employing the observation that when a mismatch occurs, the word itself embodies sufficient information to determine where the next match could begin,
thus bypassing re-examination of previously matched characters.
'''

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

print(len(ans))
print(*ans)
