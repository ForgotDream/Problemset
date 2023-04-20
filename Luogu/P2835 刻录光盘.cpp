#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

const int N = 1e5 + 50;
int n, m, ans;
int u, v;
vector<int> e[N];
stack<int> s;
int dfn[N], low[N], cnt, t, fa[N], in[N], num[N];
bool ins[N];

void tarjan(int u) {
	s.push(u), ins[u] = true;
	dfn[u] = low[u] = ++t;
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

void solve() {
	for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
	// cout << cnt << endl;
	for (int u = 1; u <= n; u++) 
		for (auto v : e[u]) if (fa[v] != fa[u]) in[fa[v]]++;
	for (int i = 1; i <= cnt; i++) if (!in[i]) ans++;
	cout << ans << endl;
	return;	
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) cin >> u >> v, e[u].push_back(v); 
	solve();
	return 0;
}