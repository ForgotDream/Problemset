#include <bits/stdc++.h>

namespace FastIO {
	char buf[1 << 23], *p1 = buf, *p2 = buf;

	inline char gc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 23, stdin), p1 == p2) ? EOF : *p1++;
	}

	template<typename T>
	inline void read(T& x) {
		x = 0;
		T f = 1;
		char c = getchar();
		while (!isdigit(c)) {
			if (c == '-') f = -1;
			c = getchar();
		}
		while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
		x *= f;
		return;
	}

	template<typename T, typename ... args>
	inline void read(T& x, args& ... tmp) {
		read(x);
		read(tmp...);
		return;
	}

	template<typename T>
	inline void print(T x) {
		if (x < 0) putchar('-'), x = -x;
		if (x / 10) print(x / 10);
		putchar(x % 10 + '0');
		return;
	}

	template<typename T>
	inline void print(T x, char c) {
		print(x), putchar(c);
		return;
	}
}

using namespace std;
using namespace FastIO;
using ll = long long;

const int N = 1e5 + 50, M = 55, INF = 0x3f3f3f3f;
int n, m;
struct Rect {
	int x1, x2, y1, y2;
} rect[M];
int x[2 * M], y[2 * M], xCnt, yCnt, xRange, yRange;

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
} dinic;

int main() {
	read(n, m);
	for (int i = 1; i <= m; i++) {
		read(rect[i].x1, rect[i].y1, rect[i].x2, rect[i].y2);
		rect[i].x2++, rect[i].y2++;
		x[++xCnt] = rect[i].x1, x[++xCnt] = rect[i].x2;
		y[++yCnt] = rect[i].y1, y[++yCnt] = rect[i].y2;
	}

	sort(x + 1, x + xCnt + 1), xRange = unique(x + 1, x + xCnt + 1) - x - 1;
	sort(y + 1, y + yCnt + 1), yRange = unique(y + 1, y + yCnt + 1) - y - 1;

	dinic.s = 0, dinic.t = xRange + yRange + 1;

	for (int i = 1; i <= m; i++) {
		rect[i].x1 = lower_bound(x + 1, x + xRange + 1, rect[i].x1) - x;
		rect[i].y1 = lower_bound(y + 1, y + yRange + 1, rect[i].y1) - y;
		rect[i].x2 = lower_bound(x + 1, x + xRange + 1, rect[i].x2) - x;
		rect[i].y2 = lower_bound(y + 1, y + yRange + 1, rect[i].y2) - y;

		for (int x = rect[i].x1; x < rect[i].x2; x++) 
			for (int y = rect[i].y1; y < rect[i].y2; y++) 
				dinic.addEdge(x, y + xRange, INF);
	}
	for (int i = 1; i < xRange; i++)
		dinic.addEdge(dinic.s, i, x[i + 1] - x[i]);
	for (int i = 1; i < yRange; i++)
		dinic.addEdge(i + xRange, dinic.t, y[i + 1] - y[i]);

	print(dinic.maxFlow(), '\n');
	return 0;
}
