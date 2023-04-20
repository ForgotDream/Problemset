#include <bits/stdc++.h>

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

const int N = 19, INF = 0x7f7f7f7f, MOD = 1e9 + 7;
int T;
ll n, m, cnt[N], f[N], powOf10[N];
int num[N + 1];

void init() {
	powOf10[0] = 1;
	for (int i = 1; i < N; i++) 
		f[i] = f[i - 1] * 10 + powOf10[i - 1], powOf10[i] = powOf10[i - 1] * 10;
	// for (int i = 1; i < N; i++) cout << f[i] << ' ';
	return;
}

ll calc(ll n) {
	memset(cnt, 0, sizeof(cnt));
	if (!n) return 0;
	int len = 0;
	while (n) num[++len] = n % 10, n /= 10;
	for (int i = len; i >= 1; i--) {
		for (int j = 0; j < 10; j++) cnt[j] = (cnt[j] + f[i - 1] * num[i] % MOD) % MOD;
		for (int j = 0; j < num[i]; j++) cnt[j] = (cnt[j] + powOf10[i - 1]) % MOD;
		ll tmp = 0;
		for (int j = i - 1; j >= 1; j--) tmp = (tmp * 10 + num[j]) % MOD;
		cnt[num[i]] = (cnt[num[i]] + tmp + 1) % MOD;
		cnt[0] -= powOf10[i - 1];   // 前导零
	}
	ll res = 0;
	for (int i = 0; i <= 9; i++) res = (res + cnt[i] * i) % MOD;
	return res;
}

int main() {
	read(T);
	init();
	while (T--) {
		read(n, m);
		print((calc(m) - calc(n - 1) + MOD) % MOD, '\n');
	}
	return 0;
}
