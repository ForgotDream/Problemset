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

const int N = 1e5 + 50;
int n, m;
ll a[N];

int main() {
    freopen("review.in", "r", stdin);
    freopen("review.out", "w", stdout);
    read(n);
    for (int i = 1; i <= n; i++) read(a[i]);
	read(m);

	while (m--) {
		int opt, l, r, x;
		read(opt);
		if (opt == 1) {
			read(l, r, x);
			for (int i = l; i <= r; i++) a[i] %= x;
		}
		else if (opt == 2) {
			read(l, x);
			a[l] += x;
		}
		else {
			read(l, r);
			ll res = 0;
			for (int i = l; i <= r; i++) res += a[i];
			print(res, '\n');
		}
	}
	return 0;
}
