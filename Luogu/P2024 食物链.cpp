#include <iostream>
#include <cstdio>

using namespace std;

const int M = 5e4 + 50;
int n, k;
int opt, x, y;
int fa[3 * M];
int ans;

int _find(int u) {
	return fa[u] == u ? u : fa[u] = _find(fa[u]);
}

void combine(int x , int y) {
	x = _find(x), y = _find(y);
	if (x != y) fa[y] = x;
	return;
}

bool check(int u, int v, int type) {
	if (type == 1) return (_find(u + n) == _find(v) || _find(u) == _find(v + n));
	else return (_find(u) == _find(v) || _find(u) == _find(v + n));
}

void init() {
	for (int i = 1; i <= 3 * n; i++) fa[i] = i;
    return;
}

int main() {
	cin >> n >> k;
    init();
	for (int i = 1; i <= k; i++) {
		cin >> opt >> x >> y;
		if (x > n || y > n) {
			ans++;
			continue;
		}
		if (opt == 1) {
			if (check(x, y, 1)) {
				ans++;
			} else {
				fa[_find(x)] = _find(y);
				fa[_find(x + n)] = _find(y + n);
				fa[_find(x + 2 * n)] = _find(y + 2 * n);
			}
		} else {
			if (check(x, y, 2)) {
				ans++;
			} else {
				fa[_find(x + n)] = _find(y);
				fa[_find(x + 2 * n)] = _find(y + n);
				fa[_find(x)] = _find(y + 2 * n);
			}
		}
	}
	cout << ans << endl;
	return 0;
}