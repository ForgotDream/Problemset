import math
import sys

sys.set_int_max_str_digits(20000)

n, m = map(int, input().split(' '))

ans = math.factorial(n + 2) * math.comb(n + 3, m)
ans = ans - 2 * math.factorial(n + 1) * math.comb(n + 2, m)

print(ans * math.factorial(m))
