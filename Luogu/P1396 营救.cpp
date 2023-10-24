#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1e4 + 50, M = 2e4 + 50;
int n, m, s ,t;
int u, v, w;
struct Edge {
	int u, v, w;
	bool operator< (const Edge& oth) const {
		return w < oth.w;
	}
} e[M];
int fa[N], all, ans;

void init() {
	for (int i = 1; i <= n; i++) fa[i] = i;
	return;
}

int get(int u) {
	return fa[u] == u ? u : fa[u] = get(fa[u]);
}

void solve() {
	init();
	sort(e + 1, e + m + 1);
	for (int i = 1; i <= m; i++) {
		int u = e[i].u, v = e[i].v, w = e[i].w;
		int fau = get(u), fav = get(v);
		if (fau != fav) {
			fa[fau] = fav;
			all++;
		}
		if (get(s) == get(t)) {
			cout << w << endl;
			return;
		}
		if (all == n - 1) break;
	}
	cout << ans << endl;
	return;
}

int main() {
	cin >> n >> m >> s >> t;
	for (int i = 1; i <= m; i++) cin >> e[i].u >> e[i].v >> e[i].w;
	solve();
	return 0;
}