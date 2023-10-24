#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
using ll = long long;

struct Edge {
	int u, v;
	ll cap, flow;

	Edge(int _u, int _v, ll _c, ll _f) : u(_u), v(_v), cap(_c), flow(_f) {};
};

const int N = 205, M = 5050;
const int INF = 0x3f3f3f3f;
int n, m, s, t;
vector<Edge> edge;
vector<int> e[N];
bool vis[N];
int dis[N], cur[N];
ll ans;

inline void addEdge(int u, int v, ll cap) {
	edge.push_back(Edge{u, v, cap, 0});
	edge.push_back(Edge{v, u, 0, 0});
	int siz = edge.size();
	e[u].push_back(siz - 2), e[v].push_back(siz - 1);
	return;
}

ll dfs(int u, ll res) {
	if (u == t || res == 0) return res;
	ll flow = 0, f;
	for (int& i = cur[u]; i < e[u].size(); i++) {
		Edge& ed = edge[e[u][i]];
		if (dis[ed.v] == dis[u] + 1 && (f = dfs(ed.v, min(res, ed.cap - ed.flow))) > 0) {
			ed.flow += f, edge[e[u][i] ^ 1].flow -= f;
			flow += f, res -= f;
			if (res == 0) break;
		}
	}
	return flow;
}

bool bfs() {
	memset(cur, 0, sizeof cur);
	memset(vis, 0, sizeof vis);
	queue<int> q;
	q.push(s), dis[s] = 0, vis[s] = true;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i : e[u]) {
			Edge& ed = edge[i];
			if (!vis[ed.v] && ed.cap > ed.flow) vis[ed.v] = true, dis[ed.v] = dis[u] + 1, q.push(ed.v);
		}
	}
	return vis[t];
}

void solve() {
	while (bfs()) {
		// memset(cur, 0, sizeof cur);
		ans += dfs(s, INF);
	}
	// print(ans, '\n');
	cout << ans << endl;
	return;
}

int main() {
	// read(n, m, s, t);
	cin >> n >> m >> s >> t;
	for (int i = 1; i <= m; i++) {
		int u, v;
		ll w;
		cin >> u >> v >> w;
		addEdge(u, v, w);
	}
	solve();
	return 0;
}