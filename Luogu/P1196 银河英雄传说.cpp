#include <iostream>
#include <cstdio>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;

const int M = 3e4 + 50;
int t;
int fa[M], d[M], num[M];
char opt;
int x, y;

void init() {
	for (int i = 1; i <= 3e4; i++) 
		fa[i] = i, num[i] = 1, d[i] = 0;
	return;
}

int find(int u) {
	if (fa[u] == u) return u;
	else {
		int ret = find(fa[u]);
		d[u] += d[fa[u]];
		return fa[u] = ret;
	}
}

void combine(int x, int y) {
	int fa_x = find(x), fa_y = find(y);
	d[fa_x] += num[fa_y];
	fa[fa_x] = fa_y;
	num[fa_y] += num[fa_x], num[fa_x] = 0;
	return;
}

void check(int x, int y) {
	int fa_x = find(x), fa_y = find(y);
	if (fa_x != fa_y) cout << -1 << endl;
	else cout << abs(d[x] - d[y]) - 1 << endl;
	return;
}

int main() {
	cin >> t;
	init();
	while (t--) {
		cin >> opt >> x >> y;
		if (opt == 'M') {
			combine(x, y);
		} else {
			check(x, y);
		}
	}
	return 0;
}