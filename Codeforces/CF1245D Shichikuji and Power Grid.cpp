#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 2050;
int n, m;
int x[N], y[N], k[N], c[N];
int fa[N];
int cnt, all;
vector<int> v1, v2;
long long ans;

struct Edge {
	int u, v;
	long long w;
	bool isZ;
	bool operator< (const Edge& oth) {
		return w < oth.w;
	}
} e[N * N];

long long calc(int i, int j) {
	return 1ll * (k[i] + k[j]) * (abs(x[i] - x[j]) + abs(y[i] - y[j]));
}

void init() {
	for (int i = 1; i <= n; i++) 
		for (int j = i + 1; j <= n; j++)
			e[++cnt] = (Edge){i, j, calc(i, j), false};
	for (int i = 1; i <= n; i++) e[++cnt] = (Edge){0, i, c[i], true};
	for (int i = 1; i <= n; i++) fa[i] = i;
	return;
}

int get(int u) {
	return u == fa[u] ? u : fa[u] = get(fa[u]);
}

void solve() {
	init();
	sort(e + 1, e + cnt + 1);
	for (int i = 1; i <= cnt; i++) {
		int u = e[i].u, v = e[i].v;
		long long w = e[i].w;
		bool z = e[i].isZ;
		if (get(u) != get(v)) {
			fa[get(u)] = get(v);
			all++, ans += w;
			if (z) v1.push_back(i);
			else v2.push_back(i);
		}
		if (all == n) break;
	}
	cout << ans << endl;
	cout << v1.size() << endl;
	for (auto i : v1) cout << e[i].v << ' ';
	cout << endl << v2.size() << endl;
	for (auto i : v2) cout << e[i].u << ' ' << e[i].v << endl;
	return;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
	for (int i = 1; i <= n; i++) cin >> c[i];
	for (int i = 1; i <= n; i++) cin >> k[i];
	solve();
	return 0;
}