/**
 * @file 	P3370 字符串哈希.cpp
 * @author 	ForgotDream
 * @brief 	String Hashing
 * @date 	2023-02-01
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
using i128 = __int128;

static const int N = 1e4 + 50, M = 1.5e3 + 50;
auto rnd = mt19937(time(0));
i64u mod;
int n, base, ans;
char str[N][M];
i64u hashing[N];

i64u getHash(char *s) {
	i64u res = 1, basePow = 1;
	int len = strlen(s);
	for (int i = 0; i < len; i++) 
		basePow = (basePow * base) % mod, res = (res + basePow * s[i] % mod) % mod;
	return res;
}

int main() {
	read(n);
	base = rnd() % 1800 + 201, mod = (i64u) rnd() * rnd() %  (int) (1e18) + 1e5 + 1;
	for (int i = 1; i <= n; i++) 
		scanf("%s", str[i]), hashing[i] = getHash(str[i]);

	sort(hashing + 1, hashing + n + 1);
	for (int i = 1; i <= n; i++) if (hashing[i] != hashing[i - 1]) ans++;
	
	print(ans, '\n');
	return 0;
}