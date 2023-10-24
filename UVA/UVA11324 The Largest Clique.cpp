#include <cstdio>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;
using Edge = pair<int, int>;

const int N = 1e5 + 50, M = 1e6 + 50;
int n, m;
int u, v;
vector<int> e[N], new_[N];
vector<Edge> ee;
stack<int> s;
queue<int> q;
int dfn[N], low[N], num[N];
bool ins[N];
int fa[N], t, cnt;
int in[N], dis[N];
int ans, kase;

void init() {
	ee.clear();
	while (!s.empty()) s.pop();
	for (int i = 1; i <= n; i++) e[i].clear();
	for (int i = 1; i <= cnt; i++) new_[i].clear();
	fill(dfn + 1, dfn + n + 1, 0), fill(low + 1, low + n + 1, 0);
	fill(num + 1, num + n + 1, 0), fill(ins + 1, ins + n + 1, 0);
	fill(in + 1, in + cnt + 1, 0), fill(dis + 1, dis + cnt + 1, 0);
	ans = 0, t = 0, cnt = 0;
	return;
}

void add(int u, int v, vector<int> *g) {
	return (void)g[u].push_back(v);
}

void tarjan(int u) {
	dfn[u] = low[u] = ++t;
	s.push(u), ins[u] = true;
	for (auto v : e[u]) {
		if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if (ins[v]) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		int p;
		++cnt;
		do {
			p = s.top(), s.pop();
			ins[p] = false, fa[p] = cnt, num[cnt]++;
		} while (p != u);
	}
	return;
}

void topo() {
	for (int i = 1; i <= cnt; i++) if (!in[i]) q.push(i), dis[i] = num[i];
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (auto v : new_[u]) {
			dis[v] = max(dis[v], dis[u] + num[v]);
			if (!--in[v]) q.push(v);
		}
	}
	return;
}

void solve() {
	for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
	for (auto i : ee) {
		int from = i.first, to = i.second;
		if (fa[from] != fa[to]) add(fa[from], fa[to], new_);
	}
	for (int i = 1; i <= cnt; i++)
		for (auto j : new_[i]) in[j]++;
	topo();
	for (int i = 1; i <= cnt; i++) ans = max(dis[i], ans);
	cout << ans << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> kase;
	while (kase--) {
		init();
		cin >> n >> m;
		for (int i = 1; i <= m; i++) cin >> u >> v, add(u, v, e), ee.emplace_back(u, v);
		solve();
	}
	return 0;
}