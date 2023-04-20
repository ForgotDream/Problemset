#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

const int N = 550;
int s, p, cnt, all;
int x[N], y[N];
int fa[N];
double ans;

struct Edge {
	int u, v;
	double w;
	bool operator< (const Edge& oth) const {
		return w < oth.w;
	}
} e[N * N];

void init() {
	for (int i = 1; i <= p; i++) fa[i] = i;
	return;
}

int get(int u) {
	return u == fa[u] ? u : fa[u] = get(fa[u]);
}

void solve() {
	for (int i = 1; i <= p; i++) 
		for (int j = i + 1; j <= p; j++) 
			e[++cnt] = (Edge){i, j, hypot(x[i] - x[j], y[i] - y[j])};
	// for (int i = 1; i <= cnt; i++) cout << e[i].u << ' ' << e[i].v << ' ' << e[i].w << endl;
	init();
	sort(e + 1, e + cnt + 1);
	for (int i = 1; i <= cnt; i++) {
		int u = e[i].u, v = e[i].v;
		double w = e[i].w;
		int fau = get(u), fav = get(v);
		if (fau != fav) fa[fau] = fav, all++, ans = max(ans, w);
		if (all == p - s) break;
	}
	cout << fixed << setprecision(2) << ans << endl;
	return;
}

int main() {
	cin >> s >> p;
	for (int i = 1; i <= p; i++) cin >> x[i] >> y[i];
	solve();
	return 0;
}