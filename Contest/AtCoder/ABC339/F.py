n = int(input())
a = n * [0]
d = dict()

for i in range(0, n):
    a[i] = int(input())
    if d.get(a[i]) == None:
        d[a[i]] = 1
    else:
        d[a[i]] += 1

ans = 0
for i in range(0, n):
    for j in range(i + 1, n):
        ans += 2 * d.get(a[i] * a[j], 0)

for i in range(0, n):
    ans += d.get(a[i] * a[i], 0);

print(ans)

