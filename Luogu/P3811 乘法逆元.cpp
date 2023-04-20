/**
 * @file 	P3811 乘法逆元.cpp
 * @author 	ForgotDream
 * @brief 	线性时间求乘法逆元
 * @date 	2023-01-30
 */

#include <bits/stdc++.h>

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
using i128 = __int128;

static const int N = 3e6 + 50;
int n, p;
i64 inv[N];

int main() {
	read(n, p);

	inv[0] = inv[1] = 1;
	for (int i = 2; i <= n; i++)
		inv[i] = (p - p / i) * inv[p % i] % p;

	for (int i = 1; i <= n; i++) 
		print(inv[i], '\n');
	return 0;
}