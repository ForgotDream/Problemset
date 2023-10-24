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

const int N = 2e5 + 50;
int n;
struct Seg {
	int l, r, col;
	bool operator< (const Seg &oth) const {
		if (r == oth.r) return l < oth.l;
		return r < oth.r;
	}
} seg[N];
multiset<int> s[2];
int ans;

int main() {
	read(n), ans = n;
	for (int i = 1; i <= n; i++) read(seg[i].l, seg[i].r, seg[i].col), seg[i].col--;

	sort(seg + 1, seg + n + 1) ;
	for (int i = 1; i <= n; i++) {
		auto &cur = s[!seg[i].col], &oth = s[seg[i].col];
		if (cur.lower_bound(seg[i].l) == cur.end()) oth.insert(seg[i].r);
		else ans--, cur.erase(cur.lower_bound(seg[i].l));
	}

	print(ans, '\n');
	return 0;
}
