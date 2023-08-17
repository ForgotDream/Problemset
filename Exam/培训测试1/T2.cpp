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
int n;
struct Point {
	int x, y;
} point[N];

bool isBigger(int i, int j) {
	return (point[i].x > point[j].x && point[i].y > point[j].y);
}

void solve() {
	ll res = 0;
	for (int i = 1; i <= n; i++) 
		for (int j = i + 1; j <= n; j++) 
			for (int k = j + 1; k <= n; k++) {
				if (isBigger(i, j) && isBigger(i, k) && (!isBigger(j, k) && !isBigger(k, j))) res++;
				if (isBigger(j, i) && isBigger(j, k) && (!isBigger(i, k) && !isBigger(k, i))) res++;
				if (isBigger(k, i) && isBigger(k, j) && (!isBigger(i, j) && !isBigger(j, i))) res++;
			}
	print(res, '\n');
	return;
}

int main() {
	read(n);
	for (int i = 1; i <= n; i++) cin >> point[i].x;
	for (int i = 1; i <= n; i++) cin >> point[i].y;
	solve();
	return 0;
}
