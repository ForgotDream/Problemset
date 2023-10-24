#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

const int M = 550, N = 1050;
int n, m, cnt, all;
int x[N], y[N];
int fa[N];
double dis[M];
double ans;

struct Edge {
	int u, v;
	double w;
	bool operator< (const Edge& oth) const {
		return w < oth.w;
	}
} e[N * N];

void init() {
	for (int i = 1; i <= n; i++) fa[i] = i;
	return;
}

int get(int u) {
	return u == fa[u] ? u : fa[u] = get(fa[u]);
}

void solve() {
	for (int i = 1; i <= n; i++) 
		for (int j = i + 1; j <= n; j++) 
			e[++cnt] = (Edge){i, j, hypot(x[i] - x[j], y[i] - y[j])};
	init();
	sort(e + 1, e + cnt + 1);
	for (int i = 1; i <= cnt; i++) {
		int u = e[i].u, v = e[i].v;
		double w = e[i].w;
		int fau = get(u), fav = get(v);
		if (fau != fav) fa[fau] = fav, all++, ans = max(ans, w);
		if (all == n - 1) break;
	}
	// cout << fixed << setprecision(2) << ans << endl;
	sort(dis + 1, dis + m + 1);
	int u = lower_bound(dis + 1, dis + m + 1, ans) - dis;
	if (dis[u] != ans) cout << m - u + 1 << endl;
	else cout << m - u + 1 << endl;
	return;
}

int main() {
	cin >> m;
	for (int i = 1; i <= m; i++) cin >> dis[i];
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
	solve();
	return 0;
}