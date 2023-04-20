/**
 * @file    P2312 解方程.cpp
 * @author  ForgotDream
 * @brief   秦九韶算法
 * @date    2023-02-20
 */
#include <bits/stdc++.h>

static const long long MOD = 1e9 + 7;

namespace FastIO{
	char buf[1 << 23], *p1 = buf, *p2 = buf;
	inline char gc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 23, stdin), p1 == p2) ? EOF : *p1++;
	}

	template<typename T>
	inline void read(T& x) {
		x = 0;
		T f = 1;
		char c = gc();
		while (!isdigit(c)) {
			if (c == '-') f = -1;
			c = gc();
		}
		while (isdigit(c)) (x = x * 10 + c - '0') %= MOD, c = gc();
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

static const int N = 110, M = 1e6 + 50;
int n, m, ans;
i64 a[N];
vector<int> ansVec;

bool calc(int num) {
	i64 sum = 0;
	for (int i = n; i; i--) {
		(sum = num * (a[i] + sum)) %= MOD;
	}
	(sum += a[0]) %= MOD;
	return (sum == 0);
}

signed main() {
	read(n, m);
	for (int i = 0; i <= n; i++) {
		read(a[i]);
	}

	for (int i = 1; i <= m; i++) {
		if (calc(i)) {
			ans++;
			ansVec.push_back(i);
		}
	}

	print(ans, '\n');
	for (auto i : ansVec) {
		print(i, '\n');
	} 
	return 0;
}