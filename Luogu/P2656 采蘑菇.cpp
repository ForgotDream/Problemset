#include <bits/stdc++.h>

using namespace std;
// using Edge = pair<int, int>;

const int N = 8e4 + 50;
int n, m, s;
struct Edge {
	int v, w, aft;
	Edge() {};
	Edge(int to, int wi, int wj) : v(to), w(wi), aft(wj) {};
};
vector<Edge> e[N], g[N];
int c[N], f[N];
stack<int> st;
int dfn[N], low[N], cnt, t, fa[N];
bool ins[N];

void tarjan(int u) {
	dfn[u] = low[u] = ++t;
	st.push(u), ins[u] = true;
	for (auto i : e[u]) {
		int v = i.v;
		if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if (ins[v]) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		++cnt;
		int p;
		do {
			p = st.top(), st.pop();
			ins[p] = false;
			fa[p] = cnt;
		} while (p != u);
	}
	return;
}

void dfs(int u) {
	if (f[u]) return;
	int tmp = 0;
	for (auto i : g[u]) {
		int v = i.v, w = i.w;
		dfs(v), tmp = max(tmp, f[v] + w);
	}
	f[u] += c[u] + tmp;
	return;
}

void solve() {
	tarjan(s);
	for (int u = 1, v, w, aft; u <= n; u++) 
		for (auto i : e[u]) {
			v = i.v, w = i.w, aft = i.aft;
			if (fa[v] == fa[u]) c[fa[u]] += aft;
			else g[fa[u]].emplace_back(fa[v], w, 0);
		}
	dfs(fa[s]);
	cout << f[fa[s]] << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, v, w = 0, tmp1, tmp2;
		long double delta;
		cin >> u >> v >> tmp1 >> delta;
		tmp2 = tmp1;
		while (tmp1) {
			w += tmp1;
			tmp1 *= delta;
		}
		e[u].emplace_back(v, tmp2, w);
		// cout << w << endl;
	}
	cin >> s;
	solve();
	return 0;
}