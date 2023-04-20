#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> Edge;

const int M = 5e3 + 50, INF = 0x3f3f3f3f;
int n, m;
int u, v, w;
int f[M], cnt[M];
bool vis[M];
vector<Edge> e[M];

Edge edge(int to, int w) {
	return make_pair(to, w);
}

bool spfa() {
	fill(f, f + n + 1, INF);
	queue<int> q;
	f[0] = 0, cnt[0] = 0;
	vis[0] = true;
	q.push(0);
	while (!q.empty()) {
		int u = q.front();
		vis[u] = false;
		q.pop();
		for (auto i : e[u]) {
			int to = i.first, w = i.second;
			if (f[to] > f[u] + w) {
				f[to] = f[u] + w;
				cnt[to] = cnt[u] + 1;
				if (cnt[to] > n) return false;
				if (!vis[to]) {
					vis[to] = true;
					q.push(to);
				}
			}
		}
	}
	return true;
}

void solve() {
	for (int i = 1; i <= n; i++) e[0].push_back(edge(i, 0));
	if (!spfa()) cout << "NO" << endl;
	else for (int i = 1; i <= n; i++) cout << f[i] << ' ';
	return;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> w;
		e[v].push_back(edge(u, w));
	}
	solve();
	return 0;
}