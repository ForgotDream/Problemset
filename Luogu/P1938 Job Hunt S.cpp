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
int d, p, c, f, s;
vector<Edge> e[225];
queue<int> q;
bool vis[225];
int dis[225];
int cnt[225];

bool spfa(int s) {
	q.push(s);
	vis[s] = true, dis[s] = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop(), vis[u] = false;
		for (auto v : e[u]) {
			int to = v.to, w = v.w;
			if (dis[to] > dis[u] + w) {
				dis[to] = dis[u] + w, cnt[to] = cnt[u] + 1;
				if (cnt[to] >= c) return false;
				if (!vis[to]) vis[to] = true, q.push(to);
			}
		}
	}
	return true;
}

void solve() {
	if (!spfa(s)) {
		cout << -1 << endl;
	} else {
		int ans = 0x3f3f3f3f;
		for (int i = 1; i <= c; i++) ans = min(ans, dis[i]);
		cout << -ans + d << endl;
	}
	return;
}

int main() {
	cin >> d >> p >> c >> f >> s;
	for (int i = 1; i <= p; i++) {
		int u, v;
		cin >> u >> v;
		e[u].push_back({v, -d});
	}
	for (int i = 1; i <= f; i++) {
		int u, v, w; 
		cin >> u >> v >> w;
		e[u].push_back({v, -d + w});
	}
	solve();
	return 0;
}