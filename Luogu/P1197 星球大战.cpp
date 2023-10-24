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
using Edge = pair<int, int>;

const int N = 2e6 + 50;
int n, m, k;
bool bucket[N];
vector<int> e[N];
vector<Edge> edge;
int fa[N], a[N], ans[N];
bool vis[N];

inline void add(int u, int v) {
	return (void) (e[u].push_back(v), edge.emplace_back(u, v));
}

inline int get(int u) {
	return u == fa[u] ? u : fa[u] = get(fa[u]);
}

void init() {
	for (int i = 1; i <= n; i++) fa[i] = i;
	return;
}

int main() {
	read(n, m);
	for (int i = 1, u, v; i <= m; i++) read(u, v), add(u + 1, v + 1), add(v + 1, u + 1);
	read(k);
	for (int i = 1; i <= k; i++) read(a[i]), vis[++a[i]] = true;

	init();

	int all = n - k;
	for (auto i : edge) {
		int u = i.first, v= i.second;
		if (!vis[u] && !vis[v])
			if (get(u) != get(v)) 
				fa[get(v)] = get(u), all--;
	}
	ans[k + 1] = all;

	for (int i = k; i; i--) {
		int u = a[i];
		all++, vis[u] = false;
		for (auto v : e[u]) 
			if (!vis[v] && get(u) != get(v)) 
				fa[get(v)] = get(u), all--;
		ans[i] = all;
	}

	for (int i = 1; i <= k + 1; i++) print(ans[i], '\n');
	return 0;
}