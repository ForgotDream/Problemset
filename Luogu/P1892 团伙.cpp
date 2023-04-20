#include <iostream>
#include <cstdio>

using namespace std;

const int M = 1e3 + 50;
int n, m;
int fa[M], enemy[M];
int count[M];
char opt;
int p, q, ans;

void init() {
	for (int i = 1; i <= n; i++) fa[i] = i;
}

int _find(int u) {
	return fa[u] == u ? u : fa[u] = _find(fa[u]);
}

void combine(int x, int y) {
	int fa_x = _find(x), fa_y = _find(y);
	if (fa_x != fa_y) fa[fa_y] = fa_x;
	return;
}

int main() {
	cin >> n >> m;
	init();
	for (int i = 1; i <= m; i++) {
		cin >> opt >> p >> q;
		if (opt == 'F') combine(p, q);
		else {
			if (enemy[p] == 0) enemy[p] = _find(q);
			else combine(q, enemy[p]);
			if (enemy[q] == 0) enemy[q] = _find(p);
			else combine(p, enemy[q]);
		}
	}
	for (int i = 1; i <= n; i++) {
		count[_find(i)]++;
	}
	for (int i = 1; i <= n; i++) {
		if (count[i]) ans++;
	}
	cout << ans << endl;
	return 0;
}