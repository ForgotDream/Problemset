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
using ll = long long;

const int N = 5e5 + 50;
int n, m, a[N];
int pre[N << 2], suf[N << 2], tot[N << 2], sum[N << 2];
struct Node {
	int pre, suf, tot, sum;
} tree[N << 2];

inline void pushup(int u) {
	int lc = u << 1, rc = u << 1 | 1;
	tree[u].sum = tree[lc].sum + tree[rc].sum;
	tree[u].pre = max(tree[lc].pre, tree[lc].sum + tree[rc].pre);
	tree[u].suf = max(tree[rc].suf, tree[rc].sum + tree[lc].suf);
	tree[u].tot = max(max(tree[lc].tot, tree[rc].tot), tree[lc].suf + tree[rc].pre);
	return;
}

inline void init(int u, int val) {
	tree[u].sum = tree[u].pre = tree[u].suf = tree[u].tot = val;
	return;
}

void build(int l, int r, int u) {
	if (l == r) return init(u, a[l]);
	int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
	build(l, mid, lc), build(mid + 1, r, rc);
	pushup(u);
	return;
}

void modify(int target, int s, int t, int u, int val) {
	if (target == s && t == target) return init(u, val);
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	if (target <= mid) modify(target, s, mid, lc, val);
	else modify(target, mid + 1, t, rc, val);
	pushup(u);
	return;
}

Node query(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return tree[u];
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	if (r <= mid) return query(l, r, s, mid, lc);
	else if (l > mid) return query(l, r, mid + 1, t, rc);
	else {
		Node L = query(l, r, s, mid, lc), R = query(l, r, mid + 1, t, rc), res;
		res.sum = L.sum + R.sum;
		res.pre = max(L.pre, L.sum + R.pre), res.suf = max(R.suf, R.sum + L.suf);
		res.tot = max(max(L.tot, R.tot), L.suf + R.pre);
		return res;
	}
}

int main() {
	read(n, m);
	for (int i = 1; i <= n; i++) read(a[i]);

	build(1, n, 1);

	while (m--) {
		int opt, x, y;
		read(opt, x, y);
		if (opt == 1) {
			if (x > y) swap(x, y);
			print(query(x, y, 1, n, 1).tot, '\n');
		}
		else modify(x, 1, n, 1, y);
	}
	return 0;
}