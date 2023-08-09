import sys

fac = [0] * int(1e3 + 50)
fac[0] = 1
for i in range(1, int(1e3 + 1)):
	fac[i] = i * fac[i - 1]

for num in sys.stdin:
	num = int(num)
	i = 2
	sum = 0
	factor = []
	while True:
		cur = 0
		while num % i == 0:
			cur += 1
			sum += 1
			num /= i
		if cur != 0:
			factor.append(cur)
		if i * i > num:
			break
		i += 1
	if num != 1:
		factor.append(1)
		sum += 1
	ans = fac[sum]
	for i in factor:
		ans /= fac[i]
	print(sum, int(ans))