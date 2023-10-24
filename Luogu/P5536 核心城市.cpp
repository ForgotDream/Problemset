#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int N = 1e5 + 50;
int n, k, res;
vector<int> e[N];
int dis[N], nxt[N], maxDis[N], tmp[N];

void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

void dfs(int u, int from) {
	maxDis[u] = dis[u] = dis[from] + 1, nxt[u] = from;
	for (int v : e[u]) {
		if (v == from) continue;
		dfs(v, u), maxDis[u] = max(maxDis[u], maxDis[v]);
	}
	return;
}

pair<int, int> getDiagrams() {
	int L = 0, R = 0;
	dfs(1, 0);
	// for (int i = 1; i <= n; i++) cerr << dis[i] << ' ';
	// cerr << endl;
	for (int i = 1; i <= n; i++) if (dis[L] < dis[i]) L = i;
	dfs(L, 0);
	for (int i = 1; i <= n; i++) if (dis[R] < dis[i]) R = i;
	return make_pair(L, R);
}

void solve() {
	auto p = getDiagrams();
	int L = p.first, R = p.second;
	int mid = R;
	for (int i = 1; i <= (dis[R]) / 2; i++) mid = nxt[mid];
	dfs(mid, 0);
	// cerr << L << ' ' << R << ' ' << mid << endl;
	for (int i = 1; i <= n; i++) tmp[i] = maxDis[i] - dis[i];
	sort(tmp + 1, tmp + n + 1, [] (int a, int b) -> bool { return a > b; });
	for (int i = k + 1; i <= n; i++) res = max(res, tmp[i] + 1);
	cout << res << endl;
	return;
}

int main() {
	cin >> n >> k;
	for (int i = 1, u, v; i < n; i++) cin >> u >> v, add(u, v), add(v, u);
	solve();
	return 0;
}