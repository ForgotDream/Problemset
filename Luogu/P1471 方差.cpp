#include <iostream>
#include <cstdio>

using namespace std;

const int N = 1e5 + 50;
int n, m;
double a[N], sum[N << 2], sqr[N << 2], add[N << 2];

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

inline void addNum(int l, int r, int u, double val) {
	sqr[u] += 2 * sum[u] * val + (r - l + 1) * val * val;
	sum[u] += (r - l + 1) * val;
	add[u] += val;
	return;
}

inline void pushup(int u) {
	sum[u] = sum[u << 1] + sum[u << 1 | 1];
	sqr[u] = sqr[u << 1] + sqr[u << 1 | 1];
	return;
}

inline void pushdown(int l, int r, int u) {
	if (add[u] == 0) return;
	int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
	addNum(l, mid, lc, add[u]), addNum(mid + 1, r, rc, add[u]);
	add[u] = 0;
	return;
}

void build(int l, int r, int u) {
	if (l == r) return (void)(sum[u] = a[l], sqr[u] = a[l] * a[l]);
	int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
	build(l, mid, lc), build(mid + 1, r, rc);
	pushup(u);
	return;
}

void modify(int l, int r, int s, int t, int u, double val) {
	if (l <= s && t <= r) return (void)(addNum(s, t, u, val));
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	pushdown(s, t, u);
	if (l <= mid) modify(l, r, s, mid, lc, val);
	if (r > mid) modify(l, r, mid + 1, t, rc, val);
	pushup(u);
	return;
}

double querySum(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return sum[u];
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	double res = 0;
	pushdown(s, t, u);
	if (l <= mid) res += querySum(l, r, s, mid, lc);
	if (r > mid) res += querySum(l, r, mid + 1, t, rc);
	return res;
}

double querySqr(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return sqr[u];
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	double res = 0;
	pushdown(s, t, u);
	if (l <= mid) res += querySqr(l, r, s, mid, lc);
	if (r > mid) res += querySqr(l, r, mid + 1, t, rc);
	return res;
}

int main() {
	read(n, m);
	for (int i = 1; i <= n; i++) scanf("%lf", &a[i]);
	build(1, n, 1);
	while (m--) {
		int opt, x, y; 
		double k;
		read(opt, x, y);
		if (opt == 1) scanf("%lf", &k), modify(x, y, 1, n, 1, k);
		else if (opt == 2) printf("%.4lf\n", querySum(x, y, 1, n, 1) / (y - x + 1));
		else {
			double aver = querySum(x, y, 1, n, 1) / (y - x + 1), sqr_ = querySqr(x, y, 1, n, 1);
			printf("%.4lf\n", sqr_ / (y - x + 1) - aver * aver);
		}
	}
	return 0;
}