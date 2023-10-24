#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int MAXN = 1e4 + 50;
struct Node {
	int u, dis, cnt;
	bool operator> (const Node& a) const {
		return dis > a.dis;
	}
};
struct Edge {
	int to, w;
};
vector<Edge> e[MAXN];
int n, m, k;
priority_queue<Node, vector<Node>, greater<Node> > pq;
bool vis[MAXN][15];
int f[MAXN][15];
int s, t;

void dijkstra(int s) {
	memset(f, 0x3f, sizeof f);
	memset(vis, 0, sizeof vis);
	f[s][0] = 0;
	pq.push({s, 0, 0});
	while (!pq.empty()) {
		auto u = pq.top().u, dis = pq.top().dis, cnt = pq.top().cnt;
		pq.pop();
		if (vis[u][cnt]) continue;
		vis[u][cnt] = true;
		for (auto v : e[u]) {
			auto to = v.to, w = v.w;
			if (cnt < k && f[to][cnt + 1] > f[u][cnt]) {
				f[to][cnt + 1] = f[u][cnt];
				pq.push({to, f[to][cnt + 1], cnt + 1});
			}
			if (f[to][cnt] > f[u][cnt] + w) {
				f[to][cnt] = f[u][cnt] + w;
				pq.push({to, f[to][cnt], cnt});
			}
		}
	}
	return;
}

void solve() {
	dijkstra(s);
	int ans = 0x3f3f3f3f;
	for (int i = 0; i <= k; i++) ans = min(ans, f[t][i]);
	cout << ans << endl;
	return;
}

int main() {
	cin >> n >> m >> k;
	cin >> s >> t;
	s++, t++;
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u++, v++;
		e[u].push_back({v, w});
		e[v].push_back({u, w});
	}
	solve();
	return 0;
}