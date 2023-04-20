/**
 * @file 	P4777 扩展中国剩余定理（EXCRT）.cpp
 * @author 	ForgotDream
 * @brief 	exCRT
 * @date 	2023-01-31
 */

#include <bits/stdc++.h>
#include <unordered_map>

namespace FastIO {
	template<typename T>
	inline void read(T& x) {
		x = 0;
		T f = 1;
		char c = getchar();
		while (!isdigit(c)) {
			if (c == '-') f = -1;
			c = getchar();
		}
		while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
		x *= f;
		return;
	}

	template<typename T, typename ... args>
	inline void read(T& x, args& ... tmp) {
		read(x);
		read(tmp...);
		return;
	}

	template<typename T>
	inline void print(T x) {
		if (x < 0) putchar('-'), x = -x;
		if (x / 10) print(x / 10);
		putchar(x % 10 + '0');
		return;
	}

	template<typename T>
	inline void print(T x, char c) {
		print(x), putchar(c);
		return;
	}
}

using namespace std;
using namespace FastIO;
using i64 = long long;
using i64u = unsigned long long;
using i128 = __int128;

static const int N = 1e5 + 50;
int n;
i128 a, b, prea, preb;
i128 x, y, ans;

i128 exgcd(i128 a, i128 b, i128 &x, i128 &y) {
	if (!b) return x = 1, y= 0, a;
	auto res = exgcd(b, a % b, x, y), t = x;
	x = y, y = t - a / b * y;
	return res;
}

i128 __lcm(i128 a, i128 b) {
	return (i128) a * b / __gcd(a, b);
}

void merge() {
	auto tmp = preb - b, gcd = exgcd(a, prea, x, y);
	if (tmp % gcd) return (void) (print(-1, '\n'));
	x = x * tmp / gcd % (prea / gcd), x += (prea / gcd) * (x < 0);
	i128 lcm = __lcm(a, prea);
	b = (a * x + b) % lcm, b += (b < 0) * lcm;
	a = lcm;
	return;
}

int main() {
	read(n);

	for (int i = 1; i <= n; i++) {
		read(prea, preb);
		if (i != 1) merge();
		else a = prea, b = preb;
	}

	print(b % a, '\n');
	return 0;
}