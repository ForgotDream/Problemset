/**
 * @file    P2065 卡片.cpp
 * @author  ForgotDream
 * @brief   最大流
 * @date    2023-02-14
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 2e4 + 50, INF = 0x3f3f3f3f;
struct Dinic {
	struct Edge {
		int u, v, cap, flow;
		Edge(int _u, int _v, int _c, int _f) : u(_u), v(_v), cap(_c), flow(_f)
		{};
	};

	vector<Edge> edge;
	vector<int> e[N];
	int n, m, s, t;
	int dis[N], cur[N];
	bool vis[N];

	int dfs(int u, int res) {
		if (u == t || res == 0) return res;
		int flow = 0, f;
		for (int& i = cur[u]; i < e[u].size(); i++) {
			Edge& ed = edge[e[u][i]];
			if (dis[ed.v] == dis[u] + 1 
				&& (f = dfs(ed.v, min(res, ed.cap - ed.flow))) > 0) {
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
				if (!vis[ed.v] && ed.cap > ed.flow) 
					vis[ed.v] = true, dis[ed.v] = dis[u] + 1, q.push(ed.v);
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

	int maxFlow() {
		int res = 0;
		while (bfs()) res += dfs(s, INF);
		return res;
	}

	void init() {
		edge.clear();
		for (int i = 0; i < N; i++) e[i].clear();
		s = 0, t = 0;
		memset(dis, 0, sizeof(dis));
		memset(cur, 0, sizeof(cur));
		return;
	}
} dinic;
int T;
int m, n;
int b[N], r[N];
int cnt, prime[N];
bool isNotPrime[N];

void getPrime(int n) {
	for (int i = 2; i <= n; i++) {
		if (!isNotPrime[i]) prime[++cnt] = i;
		for (int j = 1; j <= cnt && (i64) i * prime[j] <= n; j++) {
			isNotPrime[i * prime[j]] = true;
			if (!(i % prime[j])) break;
		}
	}
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	getPrime(1e4);

	cin >> T;
	while (T--) {
		dinic.init();

		cin >> m >> n;
		for (int i = 1; i <= m; i++) cin >> b[i];
		for (int i = 1; i <= n; i++) cin >> r[i];
		
		for (int i = 1; i <= m; i++) 
			for (int j = 1; j <= cnt && prime[j] <= b[i]; j++)
				if (b[i] % prime[j] == 0) dinic.addEdge(i, n + m + j, 1);

		for (int i = 1; i <= n; i++) 
			for (int j = 1; j <= cnt && prime[j] <= r[i]; j++)
				if (r[i] % prime[j] == 0) dinic.addEdge(n + m + j, i + m, 1);
				
		
		for (int i = 1; i <= m; i++) dinic.addEdge(0, i, 1);
		for (int i = 1; i <= n; i++) dinic.addEdge(i + m, n + m + cnt + 1, 1);

		dinic.s = 0, dinic.t = n + m + cnt + 1;
		cout << dinic.maxFlow() << '\n';
	}

	return 0;
}