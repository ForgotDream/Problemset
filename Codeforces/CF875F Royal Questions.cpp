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
int n, m;
struct Edge {
	int u, v, w;
	bool operator< (const Edge &oth) const {
		return w > oth.w;
	}
} edge[N];
int fa[N], ans;
bool circle[N];

void init() {
	for (int i = 1; i <= n; i++) fa[i] = i, circle[i] = true;
	return;
}

inline int get(int u) {
	return u == fa[u] ? u : fa[u] = get(fa[u]);
}

int main() {
	read(n, m);
	init();
	for (int i = 1; i <= m; i++) 
		read(edge[i].u, edge[i].v, edge[i].w);
	
	sort(edge + 1, edge + m + 1);
	for (int i = 1; i <= m; i++) {
		int u = edge[i].u, v = edge[i].v, w = edge[i].w;
		int fau = get(u), fav = get(v);
		if (fau != fav && (circle[fau] || circle[fav])) 
			fa[fav] = fau, ans += w, circle[fau] &= circle[fav];
		else if (fau == fav && circle[fau]) circle[fau] = false, ans += w;
	}

	print(ans, '\n');
	return 0;
}
