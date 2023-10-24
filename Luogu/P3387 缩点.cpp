#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>

using namespace std;
using Edge = pair<int, int>;

const int N = 1e4  + 50;
int n, m, u, v;
vector<int> e[N], new_[N];
vector<Edge> edge;
stack<int> s;
queue<int> q;
int a[N];
int dfn[N], low[N], num[N], t, cnt, fa[N];
bool ins[N];
int in[N], f[N], ans;

void tarjan(int u) {
	s.push(u), ins[u] = true;
	dfn[u] = low[u] = ++t;
	for (auto v : e[u]) {
		if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if (ins[v]) low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		++cnt;
		int p;
		do {
			p = s.top(), s.pop();
			ins[p] = false, num[cnt] += a[p], fa[p] = cnt;
		} while (p != u);
	}
	return;
}

void topo() {
	for (int i = 1; i <= cnt; i++) if (!in[i]) q.push(i), ans = max(f[i] = num[i], ans);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (auto v : new_[u]) {
			if (f[v] < f[u] + num[v]) f[v] = f[u] + num[v], ans = max(f[v], ans);
			if (!--in[v]) q.push(v);
		}
	}
	return (void)(cout << ans << endl);
}

void solve() {
	for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
	for (auto i : edge) {
		int from = i.first, to = i.second;
		if (fa[from] != fa[to]) new_[fa[from]].push_back(fa[to]), in[fa[to]]++;
	}
	topo();
	return;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= m; i++) cin >> u >> v, e[u].push_back(v), edge.push_back(make_pair(u, v));
	solve();
	return 0;
}