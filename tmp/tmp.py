import math

def C(n: int, m: int) -> int:
  return math.factorial(n) / (math.factorial(m) * math.factorial(n - m))

print(C(12, 6), C(12, 7))

print(math.factorial(12) / 2 ** 9)