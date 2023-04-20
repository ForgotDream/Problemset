#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
using ll = long long;

const int N = 3e5 + 50, M = 1e6 + 50;
int d[M], a[N], n, m;
ll tree[N << 2], maxx[N << 2];
int prime[M], t[M], cnt;
bool isNotPrime[M];

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

inline void init() {
	for (int i = 2; i <= M - 20; i++) {
		if (!isNotPrime[i]) prime[++cnt] = i, d[i] = 2, t[i] = 1;
		for (int j = 1; j <= cnt && i * prime[j] <= M - 20; j++) {
			isNotPrime[i * prime[j]] = true;
			if (i % prime[j] == 0) {
				t[i * prime[j]] = t[i] + 1;
				d[i * prime[j]] = d[i] * (t[i] + 2) / (t[i] + 1);
				break;
			}
			t[i * prime[j]] = 1, d[i * prime[j]] = d[i] * d[prime[j]];
		}
	}
	d[1] = t[1] = 1;
	return;
}

inline void pushup(int u) {
	return (void)(tree[u] = tree[u << 1] + tree[u << 1 | 1], maxx[u] = max(maxx[u << 1], maxx[u << 1 | 1]));
}

void build(int l, int r, int u) {
	if (l == r) return (void)(tree[u] = maxx[u] = a[l]);
	int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
	build(l, mid, lc), build(mid + 1, r, rc);
	pushup(u);
	return;
}

void update(int l, int r, int s, int t, int u) {
	if (s == t) return (void)(tree[u] = maxx[u] = d[tree[u]]);
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	if (l <= mid && maxx[lc] > 2) update(l, r, s, mid, lc);
	if (r > mid && maxx[rc] > 2) update(l, r, mid + 1, t, rc);
	pushup(u); 
	return;
}

ll query(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return tree[u];
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	ll res = 0;
	if (l <= mid) res += query(l, r, s, mid, lc);
	if (r > mid) res += query(l, r, mid + 1, t, rc);
	return res;
}

int main() {
	init();
	// for (int i = 1; i <= 20; i++) cerr << d[i] << ' ';
	// cerr << endl;
	read(n, m);
	for (int i = 1; i <= n; i++) read(a[i]);
	build(1, n, 1);
	while (m--) {
		int opt, x, y;
		read(opt, x, y);
		if (opt == 1) update(x, y, 1, n, 1);
		else print(query(x, y, 1, n, 1), '\n');
	}
	return 0;
}