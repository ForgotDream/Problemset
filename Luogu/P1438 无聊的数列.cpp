#include <iostream>
#include <cstdio>

using namespace std;
using ll = long long;

const int N = 1e5 + 50;
int n, m, a[N];
ll tree[N << 2], add[N << 2];

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
	return (void)(tree[u] = tree[u << 1] + tree[u << 1 | 1]);
}

inline void pushdown(int l , int r, int u) {
	if (!add[u]) return;
	int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
	tree[lc] += (mid - l + 1) * add[u], add[lc] += add[u];
	tree[rc] += (r - mid) * add[u], add[rc] += add[u];
	add[u] = 0;
	return;
}

void build(int l, int r, int u) {
	if (l == r) return (void)(tree[u] = a[l]);
	int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
	build(l, mid, lc), build(mid + 1, r, rc);
	pushup(u);
	return;
}

void modify(int l, int r, int s, int t, int u, ll val) {
	if (l <= s && t <= r) return (void)(tree[u] += (t - s + 1) * val, add[u] += val);
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	pushdown(s, t, u);
	if (l <= mid) modify(l, r, s, mid, lc, val);
	if (r > mid) modify(l, r, mid + 1, t, rc, val);
	pushup(u);
	return;
}

ll query(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return tree[u];
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	ll res = 0;
	pushdown(s, t, u);
	if (l <= mid) res += query(l, r, s, mid, lc);
	if (r > mid) res += query(l, r, mid + 1, t, rc);
	return res;
}

int main() {
	read(n, m);
	for (int i = 1; i <= n; i++) read(a[i]);
	for (int i = n; i >= 1; i--) a[i] -= a[i - 1];
	build(1, n, 1);
	while (m--) {
		int l, r, k, d, opt;
		read(opt);
		if (opt == 1) {
			read(l, r, k, d);
			modify(l, l, 1, n, 1, k);
			if (l + 1 <= r) modify(l + 1, r, 1, n, 1, d);
			if (r < n) modify(r + 1, r + 1, 1, n, 1, (l - r) * d - k);
		}
		else read(l), print(query(1, l, 1, n, 1), '\n');
	}
	return 0;
}