#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int N = 3e4 + 50, M = 1e5 + 50;
int tree[M << 2], n, bucket[M], cnt;
ll ans, smaller[M], bigger[M];
pii a[N];

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

void modify(int target, int s, int t, int u, int val) {
	if (s == target && t == target) return (void)(tree[u] += val);
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	if (target <= mid) modify(target, s, mid, lc, val);
	else modify(target, mid + 1, t, rc, val);
	pushup(u);
	return;
}

int query(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return tree[u];
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1, res = 0;
	if (l <= mid) res += query(l, r, s, mid, lc);
	if (r > mid) res += query(l, r, mid + 1, t, rc);
	return res;
}

int main() {
	read(n);
	for (int i = 1; i <= n; i++) read(a[i].first), a[i].second = i;
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		if (a[i].first > a[i - 1].first) ++cnt;
		bucket[a[i].second] = cnt;
	}
	for (int i = 1; i <= n; i++) {
		if (bucket[i] > 1) smaller[i] = query(1, bucket[i] - 1, 1, n, 1);
		modify(bucket[i], 1, n, 1, 1);
	}
	memset(tree, 0, sizeof tree);
	for (int i = n; i >= 1; i--) {
		if (bucket[i] < n) bigger[i] = query(bucket[i] + 1, n, 1, n, 1);
		modify(bucket[i], 1, n, 1, 1);
	}
	for (int i = 1; i <= n; i++) ans += smaller[i] * bigger[i];
	print(ans, '\n');
	return 0;
}