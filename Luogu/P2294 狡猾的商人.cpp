#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
using Edge = pair<int, int>;

const int M = 105;
int w;
int n, m;
int x, y, z;
vector<Edge> e[M];
int f[M], cnt[M];
bool vis[M];

void add(int u, int v, int w) {
	e[u].push_back(make_pair(v, w));
	return;
}

void init() {
	memset(f, 0x3f, sizeof f);
	memset(vis, 0, sizeof vis);
	memset(cnt, 0, sizeof cnt);
	for (int i = 0; i <= 100; i++) e[i].clear();
	return;
}

bool spfa(int s) {
	queue<int> q;
	q.push(s);
	f[s] = 0, vis[s] = true;
	while (!q.empty()) {
		int u = q.front();
		q.pop(), vis[u] = false;
		for (auto i : e[u]) {
			int v = i.first, w = i.second;
			if (f[v] > f[u] + w) {
				f[v] = f[u] + w;
				cnt[v] = cnt[u] + 1;
				if (cnt[v] > n) return false;
				if (!vis[v]) vis[v] = true, q.push(v);
			}
		}
	}
	return true;
}

void solve() {
	// for (int i = 1; i <= n; i++) add(0, i, 0);
	for (int i = 0; i <= n; i++) add(n + 1, i, 0);
	if (spfa(n + 1)) cout << "true" << endl;
	else cout << "false" << endl;
	return;
}

int main() {
	cin >> w;
	while (w--) {
		init();
		cin >> n >> m;
		for (int i = 1; i <= m; i++) {
			cin >> x >> y >> z;
			add(x - 1, y, z), add(y, x - 1, -z);
		}
		solve();
	}
	return 0;
}