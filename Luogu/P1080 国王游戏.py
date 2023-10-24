n = int(input())
a, b = map(int, input().split())
f = []
for i in range(0, n):
    f.append([int(j) for j in input().split()])

f.sort(key = lambda i : (i[0] * i[1]))
ans = 0
for i in range(0, n):
    ans = max(ans, a // f[i][1])
    a *= f[i][0]

print(int(ans))
