#include <bits/stdc++.h>

namespace FastIO {
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

const int N = 1e6 + 50;
int n, m;
int a[N], tree[N], ans[N];
int pre[N];
struct Query {
	int l, r, pos;
	bool operator< (const Query &oth) const {
		return r < oth.r;
	}
} query[N];

inline int lowbit(int x) {
	return x & -x;
}

void add(int x, int val) {
	for (int i = x; i <= n; i += lowbit(i)) 
		tree[i] += val; 
	return;
}

int sum(int x) {
	int res = 0;
	for (int i = x; i; i -= lowbit(i)) 
		res += tree[i];
	return res;
}

int main() {
	// 离线 + 基于数列长度的 BIT
	read(n);
	for (int i = 1; i <= n; i++) read(a[i]);
	read(m);
	for (int i = 1; i <= m; i++) read(query[i].l, query[i].r), query[i].pos = i;

	sort(query + 1, query + m + 1);

	int pivot = 1;
	for (int i = 1; i <= m; i++) {
		for (int j = pivot; j <= query[i].r; j++) {
			if (pre[a[j]]) add(pre[a[j]], -1);
			add(j, 1), pre[a[j]] = j;
		}
		pivot = query[i].r + 1, ans[query[i].pos] = sum(query[i].r) - sum(query[i].l - 1);
	}

	for (int i = 1; i <= m; i++) print(ans[i], '\n');
	return 0;
}