#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>

using namespace std;
using Edge = pair<int, int>;

const int N = 5e5 + 50;
int n, m;
int u, v;
vector<int> e[N], new_[N];
vector<Edge> edge;
stack<int> s;
int dfn[N], low[N], cnt, t, fa[N], num[N];
int a[N], st, p;
bool is_bar[N], ins[N], has_bar[N], vis[N];
int f[N], ans;
queue<int> q;

void add(int u, int v, vector<int> *e) {
	return (void)(e[u].emplace_back(v));
}

void tarjan(int u) {
	low[u] = dfn[u] = ++t;
	ins[u] = true, s.push(u);
	for (auto v : e[u]) {
		if (!dfn[v]) tarjan(v), low[u] = min(low[v], low[u]);
		else if (ins[v]) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		int p;
		cnt++;
		do {
			p = s.top(), s.pop();
			ins[p] = false;
			fa[p] = cnt, fa[p] = cnt, num[cnt] += a[p];
			has_bar[cnt] |= is_bar[p];
		} while (p != u);
	}
	return;
}

void spfa() {
	f[fa[st]] = num[fa[st]];
	q.push(fa[st]);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = false;
		for (auto v : new_[u]) 
			if (f[v] < f[u] + num[v]) {
				f[v] = f[u] + num[v];
				if (!vis[v]) vis[v] = true, q.push(v);
			}
	}
	return;
}

void solve() {
	for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
	for (auto i : edge) {
		int u = i.first, v = i.second;
		if (fa[u] != fa[v]) add(fa[u], fa[v], new_);
	}
	spfa();
	for (int i = 1; i <= cnt; i++) if (ans < f[i] && has_bar[i]) ans = f[i];
	cout << ans << endl;
	return;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) cin >> u >> v, add(u, v, e), edge.emplace_back(u, v);
	for (int i = 1; i <= n; i++) cin >> a[i];
	cin >> st >> p;
	for (int i = 1; i <= p; i++) cin >> u, is_bar[u] = true;
	solve();
	return 0;
}