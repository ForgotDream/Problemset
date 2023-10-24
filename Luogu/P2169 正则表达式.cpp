#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>

using namespace std;
using Edge = pair<int, int>;
using ll = long long;
using Point = pair<ll, int>;

struct Edge2 {
	int u, v, w;
	Edge2() {};
	Edge2(int _u, int _v, int _w = 0) : u(_u), v(_v), w(_w) {}
};

const int N = 2e5 + 50;
int n, m, u, v ,w;
vector<Edge> e[N], new_[N];
vector<Edge2> edge;
stack<int> s;
int dfn[N], low[N], fa[N], cnt, t;
priority_queue<Point> pq;
ll dis[N];
bool ins[N], vis[N];

void add(int u, int v, int w, vector<Edge> *e) {
	return (void)(e[u].emplace_back(v, w));
}

void tarjan(int u) {
	dfn[u] = low[u] = ++t;
	s.push(u), ins[u] = true;
	for (auto i : e[u]) {
		int v = i.first;
		if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if (ins[v]) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		++cnt;
		int p;
		do {
			p = s.top(), s.pop();
			fa[p] = cnt;
		} while (p != u);
	}
	return;
}

void dijkstra() {
	fill(dis + 1, dis + cnt + 1, 1e18);
	dis[fa[1]] = 0;
	pq.emplace(0ll, fa[1]);
	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();
		if (vis[u]) continue;
		vis[u] = true;
		for (auto i : new_[u]) {
			int v = i.first, w = i.second;
			if (dis[v] > dis[u] + w) dis[v] = dis[u] + w, pq.emplace(dis[v], v);
		}
	}
	return;
}

void solve() {
	for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
	// for (int i = 1; i <= n; i++) cout << fa[i] << endl;
	for (auto i : edge) {
		int u = i.u, v = i.v, w = i.w;
		// cerr << u << ' ' << v << ' ' << w << endl;
		if (fa[u] != fa[v]) add(fa[u], fa[v], w, new_);
	}
	dijkstra();
	cout << dis[fa[n]] << endl;
	return;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
		cin >> u >> v >> w, add(u, v, w, e), edge.emplace_back(u, v, w);
	solve();
	return 0;
}