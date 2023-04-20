#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

typedef pair<int, int> Node;

struct Edge {
	int to, w;
};
const int MAXN = 1e4 + 50;
int n, m, b;
int prize[MAXN];
vector<Edge> e[MAXN];
bool vis[MAXN];
int f[MAXN];

void dijkstra(int s) {
	memset(f, 0x3f, sizeof f);
	memset(vis, 0, sizeof vis);
	priority_queue<Node, vector<Node>, greater<Node> > pq;
	f[s] = 0;
	pq.push({0, s});
	while (!pq.empty()) {
		auto u = pq.top().second;
		if (vis[u]) continue;
		vis[u] = true;
		for (auto v : e[u]) {
			int to = v.to, w = v.w;
			if (f[to] > f[u] + w) f[to] = f[u] + w, pq.push({f[to], to});
		}
	}
	return;
}

void solve() {
	dijkstra(1);
	if (f[n] > b) {
		cout << "AFK" << endl;
		return;
	}
	return;
}

int main() {
	cin >> n >> m >> b;
	for (int i = 1; i <= n; i++) cin >> prize[i];
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		e[u].push_back({v, w});
		e[v].push_back({u, w});
	}
	solve();
	return 0;
}