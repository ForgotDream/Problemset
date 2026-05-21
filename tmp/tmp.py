import math

n = int(input())

ans = 0

for i in range(0, n):
    ans += 2 * math.factorial(i)

ans -= 1

for i in range(2, n + 1):
    ans -= (i - 1) * math.factorial(n - i)

print(math.factorial(n) - ans)
