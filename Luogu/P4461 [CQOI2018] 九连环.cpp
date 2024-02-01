import sys

sys.set_int_max_str_digits(35000)

t = int(input())

for _ in range(0, t):
    n = int(input())
    ans = 0
    for i in range(0, n, 2):
        ans += 2 ** i
    if n % 2 == 0:
        ans *= 2
    print(ans)
    
