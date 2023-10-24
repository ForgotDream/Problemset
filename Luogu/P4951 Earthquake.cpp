#include <iostream>
#include <cstdio>
#include <algorithm>
#include <iomanip>

using namespace std;

const int N = 450, M = 1e4 + 50;
const long double EPS = 1e-11;
int n, m;
long double l, r = 1e13, ans, f;
int fa[N], all;

struct Edge {
	int u, v;
	long double c, t, w;
	bool operator< (const Edge& oth) {
		return w < oth.w;
	}
} e[M];

void init() {
	for (int i = 1; i <= n; i++) fa[i] = i;
	return;
}

int get(int u) {
	return u == fa[u] ? u : fa[u] = get(fa[u]);
}

bool check(long double u) {
	init(), all = 0, ans = 0;
	for (int i = 1; i <= m; i++) e[i].w = u * e[i].t + e[i].c;
	sort(e + 1, e + m + 1);
	for (int i = 1; i <= m; i++) {
		int u = e[i].u, v = e[i].v;
		long double w = e[i].w;
		if (get(u) != get(v)) {
			fa[get(u)] = get(v);
			all++, ans += w;
		}
		if (all == n - 1) break;
	}
	return f < ans;
}

void solve() {
	if (check(0)) {
		cout << "0.0000" << endl;
		return;
	}
	while (r - l > EPS) {
		long double mid = (l + r) / 2;
		if (check(mid)) r = mid - EPS;
		else l = mid + EPS;
	}
	cout << fixed << setprecision(4) << l << endl;
	return;
}

int main() {
	cin >> n >> m >> f;
	for (int i = 1; i <= m; i++) cin >> e[i].u >> e[i].v >> e[i].c >> e[i].t;
	solve();
	return 0;
}