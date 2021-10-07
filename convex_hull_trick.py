import sys


def cross(j, k):
    x1, y1 = stack[j]
    x2, y2 = stack[k]
    return (y2 - y1) / (x1 - x2)


n = int(sys.stdin.readline())
a = list(map(int, sys.stdin.readline().split()))
b = list(map(int, sys.stdin.readline().split()))
stack = [(b[0], 0)]

for i in range(1, n):
    left = 0
    right = len(stack) - 1
    while left < right:
        mid = (left + right) // 2
        if cross(mid, mid + 1) <= a[i]:
            left = mid + 1
        else:
            right = mid
    
    stack.append((b[i], stack[left][0] * a[i] + stack[left][1]))
    while (len(stack) >= 3) and (cross(-2, -1) <= cross(-3, -2)):
        stack.pop(-2)

print(stack[-1][1])
