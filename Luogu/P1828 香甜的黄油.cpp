#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

typedef pair<int, int> pii;

struct Edge {
	int to, w;
};
const int M = 850, INF = 0x3f3f3f3f;
int n, p, c;
int cow[M];
vector<Edge> e[M];
bool vis[M];
int f[M], ans = 0x3f3f3f3f;
priority_queue<pii, vector<pii>, greater<pii> > pq;

void dijkstra(int s) {
	memset(f, 0x3f, sizeof f);
	memset(vis, 0, sizeof vis);
	f[s] = 0;
	pq.push({0, s});
	while (!pq.empty()) {
		auto u = pq.top().second;
		pq.pop();
		if (vis[u]) continue;
		vis[u] = true;
		for (auto v : e[u]) {
			int to = v.to, w = v.w;
			if (f[to] > f[u] + w) {
				f[to] = f[u] + w;
				pq.push({f[to], to});
			}
		}
	}
	return;
}

void solve() {
	for (int i = 1; i <= p; i++) {
		dijkstra(i);
		int tmp = 0;
		bool flag = true;
		for (int i = 1; i <= n; i++) {
			if (f[cow[i]] == INF) {
				flag = false;
				break;
			}
			tmp += f[cow[i]];
		}
		// cout << i << ' ' << tmp << endl;
		if (flag) ans = min(ans, tmp);
	}
	cout << ans << endl;
	return;
}

signed main() {
	cin >> n >> p >> c;
	for (int i = 1; i <= n; i++) cin >> cow[i];
	for (int i = 1; i <= c; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		e[u].push_back({v, w});
		e[v].push_back({u, w});
	}
	solve();
	return 0;
}