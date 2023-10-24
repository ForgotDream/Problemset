#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

const int N = 1e4 + 50, INF = N;
int tail, n;
int u, v;
vector<int> e[N];
long long d[N][3];

void add(int u, int v) {
	e[u].push_back(v);
	return;
}

void dfs(int u = 1, int fa = 0) {
	d[u][0] = 1, d[u][2] = INF;
	for (auto v : e[u]) {
		if (v == fa) continue;
		dfs(v, u);
		d[u][0] += min(d[v][0], d[v][1]);
		d[u][1] += d[v][2];
	}
	for (auto v : e[u]) {
		if (v == fa) continue;
		d[u][2] = min(d[u][2], d[u][1] - d[v][2] + d[v][0]);
	}
	// if (d[u][2] == INF) d[u][2] = 0;
	return;
}

void init() {
	memset(d, 0, sizeof d);
	for (int i = 1; i <= n; i++) e[i].clear();
	return;
}

void solve() {
	dfs();
	cout << min(d[1][0], d[1][2]) << endl;
	// cout << d[1][0] << endl;
	return;
}

int main() {
	while (cin >> n) {
		for (int i = 1; i < n; i++) 
			cin >> u >> v, add(u, v), add(v, u);
		solve(), init();
		cin >> tail;
		if (tail == -1) break;
	}
	return 0;
}