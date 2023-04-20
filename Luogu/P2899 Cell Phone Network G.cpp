#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1e4 + 50, INF = 0x3f3f3f3f;
int n;
vector<int> e[N];
int f[N][3];

inline void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

void dfs(int u, int from) {
	f[u][0] = 0, f[u][1] = 1, f[u][2] = 0;
	int pivot = 0;
	for (int v : e[u]) {
		if (v == from) continue;
		dfs(v, u);
		f[u][1] += min(min(f[v][0], f[v][1]), f[v][2]);
		f[u][2] += min(f[v][0], f[v][1]);
		if (f[pivot][1] - min(f[pivot][1], f[pivot][0]) > f[v][1] - min(f[v][1], f[v][0])) pivot = v;
	}
	f[u][0] = f[pivot][1];
	for (int v : e[u]) {
		if (v == from || v == pivot) continue;
		f[u][0] += min(f[v][0], f[v][1]);
	}
	return;
}

void solve() {
	f[0][1] = INF, dfs(1, 0);
	cout << min(f[1][0], f[1][1]) << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for (int i = 1, u, v; i < n; i++) 
		cin >> u >> v, add(u, v), add(v, u);
	solve();
	return 0;
}