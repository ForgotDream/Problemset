#include <bits/stdc++.h>

namespace FastIO {
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
		while (isdigit(c)) x = x * 10 + c - '0', c = gc();
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
using ll = long long;

const int N = 60, INF = 0x7f7f7f7f, MOD = 1e7 + 7;
ll n, f[N][N], g[N], cnt[N], oneCnt;
int len, nums[N];

inline ll fastPow(ll base, ll k, ll mod) {
	ll res = 1;
	while (k) {
		if (k & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		k >>= 1;
	}
	return res % mod;
}

void init() {
	f[0][0] = 1;
	for (int i = 1; i < N; i++) 
		for (int j = 0; j <= i; j++) {
			if (j == 0) f[i][j] = 1;
			else f[i][j] = f[i - 1][j - 1] + f[i - 1][j];
		}
	return;
}

ll calc(ll num) {
	ll res = 1;
	while (num) nums[++len] = num & 1, num >>= 1;
	for (int i = len; i; i--) 
		if (nums[i]) {
			for (int j = 1; j < i; j++) 
				cnt[j + oneCnt] += f[i - 1][j];
			cnt[++oneCnt]++;
		}
	for (int i = 2; i <= len; i++) 
		res = res * fastPow(i, cnt[i], MOD) % MOD;
	return res;
}

int main() {
	read(n);
	// cerr << n << endl;
	init();
	print(calc(n), '\n');
	return 0;
}
