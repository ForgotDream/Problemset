#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int M = 1e3 + 50;
struct Edge {
	int to, w;
};
vector<Edge> e[M];
queue<int> q;
int n, m;
bool vis[M];
int f[M], cnt[M];
int ans;

bool spfa(int s) {
	memset(f, 0x3f, sizeof f);
	memset(vis, 0, sizeof vis);
	vis[s] = true, f[s] = 0;
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = false;
		for (auto v : e[u]) {
			int to = v.to, w = v.w;
			if (f[to] > f[u] + w) {
				f[to] = f[u] + w, cnt[to] = cnt[u] + 1;
				if (cnt[to] >= n) return false;
				if (!vis[to]) q.push(to), vis[to] = true;
			}
		}
	}
	return true;
}

void solve() {
	if (spfa(1)) ans = f[n];
	else {
		cout << "Forever love" << endl;
		return;
	}
	if (spfa(n)) ans = min(ans, f[1]);
	cout << ans << endl;
	return;
};

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		e[u].push_back({v, -w});
	}
	solve();
	return 0;
}