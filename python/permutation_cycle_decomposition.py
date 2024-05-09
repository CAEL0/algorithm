# BOJ 10451 순열 사이클

import sys
input = sys.stdin.readline

for _ in range(int(input())):
    N = int(input())
    A = [*map(lambda x: int(x) - 1, input().split())]
    ans = 0
    vst = [0] * N
    for i in range(N):
        if not vst[i]:
            vst[i] = 1
            ans += 1
            while True:
                i = A[i]
                if vst[i]:
                    break
                vst[i] = 1
    
    print(ans)
