#include <iostream>
#include <cstdio>

using namespace std;

const int N = 5e4 + 50;
int n, m;
int sum[N << 3], lMax[N << 3], rMax[N << 3], lzy[N << 3];

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

inline void pushup(int l, int r, int u) {
	int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
	if (sum[lc] == mid - l + 1) lMax[u] = sum[lc] + lMax[rc];
	else lMax[u] = lMax[lc];
	if (sum[rc] == r - mid) rMax[u] = sum[rc] + rMax[lc];
	else rMax[u] = rMax[rc];
	sum[u] = max(max(sum[lc], sum[rc]), rMax[lc] + lMax[rc]);
	return;
}

inline void pushdown(int l, int r, int u) {
	int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
	if (lzy[u] == 0) return;
	else if (lzy[u] == 1) sum[lc] = lMax[lc] = rMax[lc] = 0, sum[rc] = lMax[rc] = rMax[rc] = 0;
	else sum[lc] = lMax[lc] = rMax[lc] = mid - l + 1, sum[rc] = lMax[rc] = rMax[rc] = r - mid;
	lzy[lc] = lzy[rc] = lzy[u], lzy[u] = 0;
	return;
}

void build(int l, int r, int u) {
	sum[u] = lMax[u] = rMax[u] = r - l + 1;
	if (l == r) return;
	int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
	build(l, mid, lc), build(mid + 1, r, rc);
	// pushup(l, r, u);
	return;
}

void modify(int l, int r, int s, int t, int u, int val) {
	pushdown(s, t, u);
	if (l <= s && t <= r) {
		lzy[u] = val;
		if (val == 1) sum[u] = 0, lMax[u] = 0, rMax[u] = 0;
		else sum[u] = t - s + 1, lMax[u] = t - s + 1, rMax[u] = t - s + 1;
		return;
	}
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	if (l <= mid) modify(l, r, s, mid, lc, val);
	if (r > mid) modify(l, r, mid + 1, t, rc, val);
	pushup(s, t, u);
	return;
}

int query(int l, int r, int u, int len) {
	pushdown(l, r, u);
	if (l == r) return l;
	int lc = u << 1, rc = u << 1 | 1, mid = (l + r) >> 1;
	if (sum[lc] >= len) return query(l, mid, lc, len);
	else if (lMax[rc] + rMax[lc] >= len) return mid - rMax[lc] + 1;
	else return query(mid + 1, r, rc, len);
}

int main() {
	read(n, m);
	build(1, n, 1);
	while (m--) {
		int opt, x, y;
		read(opt);
		if (opt == 1) {
			read(x);
			// cerr << '#' << sum[1] << endl;
			if (sum[1] >= x) {
				int tmp = query(1, n, 1, x);
				modify(tmp, tmp + x - 1, 1, n, 1, 1);
				print(tmp, '\n');
			} else print(0, '\n');
		} else {
			read(x, y);
			modify(x, x + y - 1, 1, n, 1, -1);
			// pushup(1, n, 1);
		}
	}
	return 0;
}