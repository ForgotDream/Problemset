#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
using ll = long long;

struct Edge {
	int u, v, cap, flow;

	Edge(int _u, int _v, int _c, int _f) : u(_u), v(_v), cap(_c), flow(_f) {};
};

const int N = 5050, M = 5050;
const int INF = 0x3f3f3f3f;
int n, m, s, t, k;
vector<Edge> edge;
vector<int> e[N];
bool vis[N];
int dis[N], cur[N];
int ans;

inline void addEdge(int u, int v, int cap) {
	edge.push_back(Edge{u, v, cap, 0});
	edge.push_back(Edge{v, u, 0, 0});
	int siz = edge.size();
	e[u].push_back(siz - 2), e[v].push_back(siz - 1);
	return;
}

int dfs(int u, int res) {
	if (u == t || res == 0) return res;
	int flow = 0, f;
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
	while (bfs()) ans += dfs(s, INF);
	if (ans != m) return (void)(cout << "No solution!" << endl);
	else for (int i = 1; i <= k; i++) {
		cout << i << ": ";
		for (int j : e[n + i]) {
			Edge ed = edge[j];
			// cout << ed.flow << ' ' << ed.cap << ' ' << ed.v << endl;
			if (ed.flow < 0 && ed.v <= n) cout << ed.v << ' ';
		}
		cout << endl;
	}
	return;
}

int main() {
	cin >> k >> n;
	s = n + k + 1, t = s + 1;
	for (int i = 1, w; i <= k; i++) 
		cin >> w, m += w, addEdge(n + i, t, w);
	for (int i = 1, p, type; i <= n; i++) {
		addEdge(s, i, 1), cin >> p;
		while (p--) cin >> type, addEdge(i, n + type, 1);
	}
	solve();
	return 0;
}