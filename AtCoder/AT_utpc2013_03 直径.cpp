#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int N = 1e3 + 50;
int n, m;
int firMin = N, firMax, secMin = N, secMax;
vector<int> e[N];
bool vis[N];
int dis[N], tmp = 0;

inline void init() {
	for (int i = 1; i <= n; i++) e[i].clear();
	return;
}

void bfs(int s) {
	fill(vis + 1, vis + n + 1, 0), fill(dis + 1, dis + n + 1, 0);
	queue<int> q;
	q.push(s), vis[s] = true;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v : e[u]) {
			if (vis[v]) continue;
			vis[v] = true, dis[v] = dis[u] + 1, q.push(v);
		}
	}
	return;
}

inline void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1, u, v; i <= m; i++) cin >> u >> v, add(u + 1, v + 1), add(v + 1, u + 1);
	for (int i = 1; i <= n; i++) {
		bfs(i), tmp = 0;
		for (int i = 1; i <= n; i++) tmp = max(tmp, dis[i]);
		firMin = min(tmp, firMin), firMax = max(tmp, firMax);
	}
	init();
	cin >> n >> m;
	for (int i = 1, u, v; i <= m; i++) cin >> u >> v, add(u + 1, v + 1), add(v + 1, u + 1);
	for (int i = 1; i <= n; i++) {
		bfs(i), tmp = 0;
		for (int i = 1; i <= n; i++) tmp = max(tmp, dis[i]);
		secMin = min(tmp, secMin), secMax = max(tmp, secMax);
	}
	cout << max(max(firMax, secMax), firMin + secMin + 1) << ' ' << firMax + secMax + 1 << endl;
	return 0;
}