#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1e5 + 50;
int n, m, k;
int all, ans;
int fa[N];

struct Edge {
	int u, v, w;
	bool operator<(const Edge& oth) const {
		return w > oth.w;
	}
} e[N];

void init() {
	for (int i = 1; i <= n; i++) fa[i] = i;
	return;
}

int get(int u) {
	return u == fa[u] ? u : fa[u] = get(fa[u]);
}

void solve() {
	sort(e + 1, e + m + 1);
	init();
	for (int i = 1; i <= m; i++) {
		int u = e[i].u, v = e[i].v, w = e[i].w;
		if (get(u) != get(v)) {
			fa[get(u)] = get(v);
			all++, ans += w;
		}
		if (all == k) break;
	}
	cout << ans << endl;
	return;
}

int main() {
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i++) cin >> e[i].u >> e[i].v >> e[i].w;
	solve();
	return 0;
}