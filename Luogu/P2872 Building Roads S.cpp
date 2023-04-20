#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

const int M = 1e3 + 50;
struct Edge {
	int u, v;
	double w;
	bool operator< (const Edge& oth) {
		return w < oth.w;
	}
} e[M * M];
struct Point {
	int x, y;
} p[M];
int n, m, u, v, cnt;
int fa[M * M], all;
double ans;

void init() {
	for (int i = 1; i <= n; i++) fa[i] = i;
	return;
}

int get(int u) {
	return u == fa[u] ? u : fa[u] = get(fa[u]);
}

void solve() {
	init();
	for (int i = 1; i <= cnt; i++) {
		int u = e[i].u, v = e[i].v;
		double w = e[i].w;
		int fau = get(u), fav = get(v);
		// cout << fau << ' ' << fav << endl;
		if (fau != fav) fa[fau] = fav, ans += w, all++;
		if (all == n - 1) break;
	}
	cout << fixed << setprecision(2) << ans << endl;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> p[i].x >> p[i].y;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		e[++cnt] = (Edge){u, v, 0}; // , e[++cnt] = (Edge){v, u, 0};
	}
	for (int i = 1; i <= n; i++) 
		for (int j = i + 1; j <= n; j++) {
			e[++cnt] = (Edge){i, j, hypot(p[i].x - p[j].x, p[i].y - p[j].y)};
			// e[++cnt] = (Edge){j, i, hypot(p[i].x - p[j].x, p[i].y - p[j].y)};
		}
	sort(e + 1, e + cnt + 1);
	// cout << e[5].u << ' ' << e[5].v << ' ' << e[5].w << endl;
	solve();
	return 0;
}