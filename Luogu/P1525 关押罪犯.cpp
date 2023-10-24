#include <iostream>
#include <cstdio>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;

const int M = 1e5 + 50, N = 2e4 + 50;
struct event {
	int a, b, c;
	bool operator< (const event& x) const {
		return c > x.c;
	}
} e[M];
int n, m;
int fa[N], enemy[N];

void init() {
	for (int i = 1; i <= n; i++) fa[i] = i;
	return;
}

int find(int u) {
	return fa[u] == u ? u : fa[u] = find(fa[u]);
}

void combine(int x, int y) {
	int fa_x = find(x), fa_y = find(y);
	if (fa_x != fa_y) fa[fa_y] = fa_x;
	return;
}

int main() {
	cin >> n >> m;
	init();
	for (int i = 1; i <= m; i++) {
		cin >> e[i].a >> e[i].b >> e[i].c;
	}
	std::sort(e + 1, e + m + 1);
	for (int i = 1; i <= m; i++) {
		int fa_a = find(e[i].a), fa_b = find(e[i].b);
		if (fa_a == fa_b) return cout << e[i].c << endl, 0;
		if (!enemy[e[i].a]) enemy[e[i].a] = e[i].b;
		else fa[find(enemy[e[i].a])] = find(e[i].b);
		if (!enemy[e[i].b]) enemy[e[i].b] = e[i].a;
		else fa[find(enemy[e[i].b])] = find(e[i].a);	
	}
	return cout << 0 << endl, 0;
}