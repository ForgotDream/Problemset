#include <iostream>
#include <cstdio>

using namespace std;

const int N = 150010, M = 3 * N;
int n, m, a[N], pivot = N, cnt[(M + 10)];
int minn[(M + 10) << 2], minnCnt[(M + 10) << 2], add[(M + 10) << 2], zeroCnt[(M + 10) << 2];

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
	int lc = u << 1, rc = u << 1 | 1;
	minn[u] = min(minn[lc], minn[rc]), minnCnt[u] = 0;
	zeroCnt[u] = zeroCnt[lc] + zeroCnt[rc];
	if (minn[u] == minn[lc]) minnCnt[u] += minnCnt[lc];
	if (minn[u] == minn[rc]) minnCnt[u] += minnCnt[rc];
	return;
}

inline void pushdown(int u) {
	if (!add[u]) return;
	int lc = u << 1, rc = u << 1 | 1;
	minn[lc] += add[u], add[lc] += add[u], zeroCnt[lc] = (!minn[lc]) ? minnCnt[lc] : 0;
	minn[rc] += add[u], add[rc] += add[u], zeroCnt[rc] = (!minn[rc]) ? minnCnt[rc] : 0;
	add[u] = 0;
	return;
}

void build(int l, int r, int u) {
	if (l == r) return (void)(minnCnt[u] = 1, zeroCnt[u] = 1);
	int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
	build(l, mid, lc), build(mid + 1, r, rc);
	pushup(u);
	return;
}

void modify(int l, int r, int s, int t, int u, int val) {
	if (l <= s && t <= r) 
		return (void)(minn[u] += val, add[u] += val, zeroCnt[u] = (!minn[u]) ? minnCnt[u] : 0);
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	pushdown(u);
	if (l <= mid) modify(l, r, s, mid, lc, val);
	if (r > mid) modify(l, r, mid + 1, t, rc, val);
	pushup(u);
	return;
}

int query(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return zeroCnt[u];
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1, res = 0;
	pushdown(u);
	if (l <= mid) res += query(l, r, s, mid, lc);
	if (r > mid) res += query(l, r, mid + 1, t, rc);
	return res;
}

int main() {
	build(1, M, 1);
	read(n, m);
	for (int i = 1; i <= n; i++) read(a[i]), a[i] += pivot, cnt[a[i]]++;
	for (int i = pivot + 1; i <= pivot + n; i++) if (cnt[i]) modify(i - cnt[i] + 1, i, 1, M, 1, 1);
	while (m--) {
		int p, x;
		read(p, x);
		if (p) {
			if (a[p] <= pivot + n) modify(a[p] - cnt[a[p]] + 1, a[p] - cnt[a[p]] + 1, 1, M, 1, -1);
			cnt[a[p]]--, a[p] = pivot + x, cnt[a[p]]++;
			if (a[p] <= pivot + n) modify(a[p] - cnt[a[p]] + 1, a[p] - cnt[a[p]] + 1, 1, M, 1, 1);
		} else {
			if (x == -1) {
				++pivot;
				if (cnt[pivot + n]) modify(pivot + n - cnt[pivot + n] + 1, pivot + n, 1, M, 1, 1);
			} else {
				if (cnt[pivot + n]) modify(pivot + n - cnt[pivot + n] + 1, pivot + n, 1, M, 1, -1);
				pivot--;
			}
		}
		print(query(pivot + 1, pivot + n, 1, M, 1), '\n');
	}
	return 0;
}