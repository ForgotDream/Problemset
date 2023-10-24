/**
 * @file 	P2485 计算器.cpp
 * @author 	ForgotDream
 * @brief 	BSGS + FastPow + EXgcd 数学水题
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

static const int N = 1.5e7 + 50;
int T, type;
unordered_map<i64, i64> mp;

i64 fastPow(i64 base, i64 p, i64 mod) {
	i64 res = 1;
	base %= mod;
	while (p) {
		if (p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
	if (!b) return x = 1, y = 0, a;
	i64 res = exgcd(b, a % b, x, y), tmp = x;
	x = y, y = tmp - a / b * y;
	return res;
}

i64 bsgs(i64 base, i64 rst, i64 mod) {
	if (!(base % mod) && rst) return -1;
	if (!(base % mod) && !rst) return 1;
	mp.clear();
	i64 cur = 1, t = ceil(sqrt(mod));
	for (int i = 1; i <= t; i++) 
		cur = cur * base % mod, mp[cur * rst % mod] = i;
	i64 now = cur;
	for (int i = 1; i <= t; i++) {
		if (mp[now]) return (i64) i * t - mp[now];
		now = now * cur % mod;
	}
	return -1;
}

int main() {
	read(T, type);
	while (T--) {
		i64 y, z, p, a, b;
		read(y, z, p);
		if (type == 1) print(fastPow(y, z, p), '\n');
		else if (type == 2) {
			i64 gcd = exgcd(y, p, a, b);
			if (z % gcd) printf("Orz, I cannot find x!\n");
			else {
				while (a < 0) a += p / gcd;
				print(((a * z) / gcd % (p / gcd) + (p / gcd)) % (p / gcd), '\n');
			}
		}
		else {
			a = bsgs(y, z % p, p);
			if (!(~a)) printf("Orz, I cannot find x!\n");
			else print(a, '\n');
		}
	}
	return 0;
}