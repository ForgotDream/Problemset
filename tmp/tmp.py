import math

def lowerPow(n: int, exp: int) -> int:
  res = 1
  for i in range(n - exp + 1, n + 1):
    res *= i
  return res

res = 0
p = 7
for i in range(98):
  print(math.comb(2 * i, i) * math.comb(196, 2 * i))