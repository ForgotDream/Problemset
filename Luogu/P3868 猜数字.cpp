/**
 * @file 	P3868 猜数字.cpp
 * @author 	ForgotDream
 * @brief 	CRT
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

static const int N = 15;
int k;
i128 a[N], b[N];

i128 exgcd(i128 a, i128 b, i128 &x, i128 &y) {
	if (!b) return x = 1, y = 0, a;
	i128 res = exgcd(b, a % b, x, y), tmp = x;
	x = y, y = tmp - a / b * x;
	return res;
}

i128 CRT() {
	i128 m = 1, res = 0;
	for (int i = 1; i <= k; i++) m *= b[i];
	for (int i = 1; i <= k; i++) {
		i128 k = m / b[i], x, y;
		exgcd(k, b[i], x, y);
		res = (res + a[i] * k * x % m) % m;
	}
	return (res % m + m) % m;
}

int main() {
	read(k);
	for (int i = 1; i <= k; i++) read(a[i]);
	for (int i = 1; i <= k; i++) read(b[i]);

	for (int i = 1; i <= k; i++) a[i] = (a[i] % b[i] + 10 * b[i]) % b[i];

	print(CRT(), '\n');
	return 0;
}