#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int M = 5e3 + 50;
struct Edge {
	int to, w;
};
int n, m;
vector<Edge> e[M];
queue<int> q;
bool vis[M];
int f[M], cnt[M];

bool spfa(int s) {
	memset(f, 0x3f, sizeof(f));
	vis[s] = true, f[s] = 0;
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop(), vis[u] = false;
		for (auto v : e[u]) {
			int to = v.to, w = v.w;
			if (f[to] > f[u] + w) {
				f[to] = f[u] + w, cnt[to] = cnt[u] + 1;
				if (cnt[to] >= n) return false;
				if (!vis[to]) vis[to] = true, q.push(to);
			}
		}
	}
	return true;
}

void solve() {
	for (int i = 1; i <= n; i++) e[0].push_back({i, 0});
	if (spfa(0)) cout << "Yes" << endl;
	else cout << "No" << endl;
	return;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int o;
		int u, v, w;
		cin >> o;
		if (o == 1) {
			cin >> u >> v >> w;
			e[u].push_back({v, -w});
		} else if (o == 2) {
			cin >> u >> v >> w;
			e[v].push_back({u, w});
		} else {
			cin >> u >> v;
			e[u].push_back({v, 0}), e[v].push_back({u, 0});
		}
	}
	solve();
	return 0;
}