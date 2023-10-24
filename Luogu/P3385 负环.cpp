#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int M = 2e3 + 50;
struct Edge {
	int to, w;
};
int t;
int n, m;
bool vis[M];
int f[M], cnt[M];
int times[M];
vector<Edge> e[M];

bool solve() {
	memset(f, 0x3f, sizeof f);
	memset(vis, 0, sizeof vis);
	memset(cnt, 0, sizeof cnt);
	queue<int> q;
	q.push(1);
	f[1] = 0; vis[1] = true;
	while (!q.empty()) {
		int u = q.front();
		q.pop(), vis[u] = false;
		for (auto i : e[u]) {
			int to = i.to, w = i.w;
			if (f[to] > f[u] + w) {
				f[to] = f[u] + w, cnt[to] = cnt[u] + 1;
				if (cnt[to] >= n) return false;
				// if (to == 1) return false;
				if (!vis[to]) vis[to] = true, q.push(to);
			}
		}
	}
	return true;
}

int main() {
	cin >> t;
	while (t--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++) e[i].clear();
		for (int i = 1; i <= m; i++) {
			int u, v, w;
			cin >> u >> v >> w;
			e[u].push_back({v, w});
			if (w >= 0) e[v].push_back({u, w});
		}
		if (solve()) cout << "NO" << endl;
		else cout << "YES" << endl;
	}
	return 0;
}