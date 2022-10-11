import sys
input = sys.stdin.readline

v, e = map(int, input().split())
parent = [i for i in range(v + 1)]
graph = sorted([tuple(map(int, input().split())) for _ in range(e)], key=lambda x: x[2])


def union(x, y):
    parent[find(x)] = find(y)


def find(z):
    if z != parent[z]:
        parent[z] = find(parent[z])
    return parent[z]


ans = 0
cnt = 0
for x, y, w in graph:
    if find(x) != find(y):
        union(x, y)
        ans += w
        cnt += 1
    
    if cnt == v - 1:
        print(ans)
        break
else:
    print(-1)
