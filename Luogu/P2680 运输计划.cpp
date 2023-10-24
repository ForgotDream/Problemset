/**
 * @file    P2680 运输计划.cpp
 * @author  ForgotDream
 * @brief   LCA + Binary Search
 * @date    2023-02-10
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i128 = __int128;
using Edge = pair<int, int>;

static const int N = 3e5 + 50;
int n, m, sum;
vector<Edge> e[N];
int fa[N][25], dis[N], dep[N], dfn[N], clk;
struct Query {
	int u, v, lca, dis;
} query[N];

inline void add(int u, int v, int w) {
	return (void) (e[u].emplace_back(v, w));
}

void dfs(int u, int from) {
	dfn[++clk] = u;
	fa[u][0] = from, dep[u] = dep[from] + 1;
	for (int i = 1; (1 << i) < dep[u]; i++) 
		fa[u][i] = fa[fa[u][i - 1]][i - 1];

	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (v == from) continue;
		dis[v] = dis[u] + w, dfs(v, u);
	}
	return;
}

int getLCA(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	
	for (int i = 24; ~i; i--) 
		if (dep[x] - (1 << i) >= dep[y]) x = fa[x][i];
	if (x == y) return x;

	for (int i = 24; ~i; i--) 
		if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

bool check(int ans) {
	static int tmp[N];
	memset(tmp, 0, sizeof(tmp));
	int maxx = 0, cnt = 0;
	for (int i = 1; i <= m; i++) 
		if (query[i].dis > ans) {
			tmp[query[i].u]++, tmp[query[i].v]++, tmp[query[i].lca] -= 2;
			maxx = max(maxx, query[i].dis - ans), cnt++;
		}

	if (!cnt) return true;
	for (int i = n; i; i--) tmp[fa[dfn[i]][0]] += tmp[dfn[i]];
	for (int i = 2; i <= n; i++) 
		if (tmp[i] == cnt && dis[i] - dis[fa[i][0]] >= maxx) return true;
	
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n >> m;
	for (int i = 1, u, v, w; i < n; i++) {
		cin >> u >> v >> w;
		add(u, v, w), add(v, u, w), sum += w;
	}

	dfs(1, 0);

	for (int i = 1; i <= m; i++) {
		cin >> query[i].u >> query[i].v;
		query[i].lca = getLCA(query[i].u, query[i].v);
		query[i].dis = dis[query[i].u] + dis[query[i].v] - 2 * dis[query[i].lca];
		// cerr << query[i].dis << '\n';
	}

	int l = 0, r = sum;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}

	cout << l << '\n';

	return 0;
}