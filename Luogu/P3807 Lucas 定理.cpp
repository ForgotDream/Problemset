/**
 * @file 	P3807 Lucas 定理.cpp
 * @author 	ForgotDream
 * @brief 	Lucas 定理
 * @date 	2023-01-30
 */

#include <bits/stdc++.h>
#include <random>

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

static const int N = 1e5 + 50;
int T;
int n, m, p;
i64 fac[N];

i64 fastPow(i64 base, int t) {
	i64 res = 1;
	base %= p;
	while (t) {
		if (t & 1) res = (res * base) % p;
		base = (base * base) % p;
		t >>= 1;
	}
	return res;
}

i64 C(int n, int m) {
	if (m > n) return 0;
	return fac[n] * fastPow(fac[n - m], p - 2) * fastPow(fac[m], p - 2) % p;
}

i64 Lucas(int n, int m) {
	if (!m) return 1ll;
	return Lucas(n / p, m / p) * C(n % p, m % p) % p;
}

int main() {
	read(T);
	while (T--) {
		read(n, m, p);
		fac[0] = 1;
		// 预处理阶乘
		for (int i = 1; i <= p; i++) fac[i] = fac[i - 1] * i % p;
		print(Lucas(n + m, n), '\n');
	}
	return 0;
}