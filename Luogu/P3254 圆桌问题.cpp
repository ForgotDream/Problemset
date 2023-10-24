#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int N = 5050, INF = 0x3f3f3f3f;

struct Edge {
	int u, v, cap, flow;
	Edge(int _u, int _v, int _c, int _f) : u(_u), v(_v), cap(_c), flow(_f) {};
};

vector<Edge> edge;
vector<int> e[N];
int n, m, s, t;
int dis[N], cur[N];
int ans, all;
bool vis[N];

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

inline void addEdge(int u, int v, int cap) {
	edge.push_back(Edge{u, v, cap, 0});
	edge.push_back(Edge{v, u, 0, 0});
	int siz = edge.size();
	e[u].push_back(siz - 2), e[v].push_back(siz - 1);
	return;
}

void solve() {
	int t = 0;
	while (bfs()) ans += dfs(s, INF);
	// cerr << "OK" << endl;
	// cerr << ans << ' ' << all << endl; 
	if (ans != all) return (void)(cout << 0 << endl);
	else {
		cout << 1 << endl;
		for (int i = 1; i <= m; i++) {
			for (auto v : e[i]) {
				Edge &ed = edge[v];
				if (ed.v != s && ed.flow) cout << ed.v - m << ' ';
			}
			cout << endl;
		}
	}
	return;
}

int main() {
	cin >> m >> n;
	s = m + n + 1, t = s + 1;
	for (int i = 1; i <= m; i++) 
		for (int j = 1; j <= n; j++) addEdge(i, j + m, 1);
	for (int i = 1, mi; i <= m; i++) cin >> mi, all += mi, addEdge(s, i, mi);
	for (int i = 1, ni; i <= n; i++) cin >> ni, addEdge(i + m, t, ni);
	solve();
	return 0;
}