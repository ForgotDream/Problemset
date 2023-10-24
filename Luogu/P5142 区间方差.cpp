#include <iostream>
#include <cstdio>

using namespace std;
using ll = long long;

const int N = 1e5 + 50, MOD = 1e9 + 7;
int a[N], n, m;
ll sum[N << 2], sqr[N << 2];

template<typename T>
inline void read(T& x) {
	x = 0;
	T f = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
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

inline void pushup(int u) {
	sum[u] = (sum[u << 1] + sum[u << 1 | 1]) % MOD;
	sqr[u] = (sqr[u << 1] + sqr[u << 1 | 1]) % MOD;
	return;
}

void build(int l, int r, int u) {
	if (l == r) return (void)(sum[u] = a[l], sqr[u] = (ll)a[l] * a[l] % MOD);
	int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
	build(l, mid, lc), build(mid + 1, r, rc);
	pushup(u);
	return;
}

void modify(int target, int s, int t, int u, int val) {
	if (s == target && t == target) 
		return (void)(sum[u] = val % MOD, sqr[u] = (ll)val * val % MOD);
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	if (target <= mid) modify(target, s, mid, lc, val);
	else modify(target, mid + 1, t, rc, val);
	pushup(u);
	return;
}

int querySum(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return sum[u];
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1, res = 0;
	if (l <= mid) res = (res + querySum(l, r, s, mid, lc)) % MOD;
	if (r > mid) res = (res + querySum(l, r, mid + 1, t, rc)) % MOD;
	return res;
}

int querySqr(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return sqr[u];
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1, res = 0;
	if (l <= mid) res = (res + querySqr(l, r, s, mid, lc)) % MOD;
	if (r > mid) res = (res + querySqr(l, r, mid + 1, t, rc)) % MOD;
	return res;
}

inline int fastPower(int base, int p, int m) {
	int res = 1;
	while(p) {
		if (p & 1) res = ((ll)res * base) % m;
		base = ((ll)base * base) % m;
		p >>= 1;
	}
	return res;
}

int main() {
	read(n, m);
	for (int i = 1; i <= n; i++) read(a[i]);
	build(1, n, 1);
	while (m--) {
		int opt, x, y;
		read(opt, x, y);
		if (opt == 1) modify(x, 1, n, 1, y);
		else {
			int sum_ = querySum(x, y, 1, n, 1), sqr_ = querySqr(x, y, 1, n, 1);
			int inv = fastPower(y - x + 1, MOD - 2, MOD), aver = (ll)inv * sum_ % MOD;
			int ans = (ll)inv * sqr_ % MOD - (ll)aver * aver % MOD;
			ans = (ans % MOD + (ll)3 * MOD) % MOD;
			print(ans, '\n');
		}
	}
	return 0;
}