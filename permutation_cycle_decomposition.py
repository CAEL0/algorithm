# BOJ 10451 순열 사이클

import sys
input = sys.stdin.readline

for _ in range(int(input())):
    n = int(input())
    arr = [*map(lambda x: int(x) - 1, input().split())]
    ans = 0
    visit = [0] * n
    for i in range(n):
        if not visit[i]:
            visit[i] = 1
            ans += 1
            while True:
                i = arr[i]
                if visit[i]:
                    break
                visit[i] = 1
    
    print(ans)
