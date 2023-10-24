/**
 * @file 	P5431 乘法逆元 2.cpp
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

static const int N = 5e6 + 50;
int n, p, k;
i64 pre[N], suf[N], a[N], ans;

int getInv(int num) {
	if (num == 1) return 1;
	return (i64) (p - p / num) * getInv(p % num) % p;
}

int main() {
	read(n, p, k);
	for (int i = 1; i <= n; i++) read(a[i]);

	pre[0] = suf[n + 1] = 1;
	for (int i = 1; i <= n; i++) pre[i] = (i64) pre[i - 1] * a[i] % p;
	for (int i = n; i; i--) suf[i] = (i64) suf[i + 1] * a[i] % p;

	for (i64 i = 1, j = k; i <= n; i++, j = (i64) j * k % p) 
		ans = (i64) (ans + j * pre[i - 1] % p * suf[i + 1] % p) % p;
	// cerr << "OK" << '\n';
	ans = (i64) (ans * getInv(suf[1])) % p;

	print(ans, '\n');  
	return 0;
}