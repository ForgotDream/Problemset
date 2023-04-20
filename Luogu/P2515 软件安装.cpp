#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

const int N = 105, M = 550;
int n, m;
int w[N], v[N], d[N];
int new_w[N], new_v[N];
vector<int> e[N], new_[N];
int dfn[N], low[N], fa[N], cnt, t;
stack<int> s;
bool ins[N];
int in[N];
int dp[N][M];

int add(int u, int v, vector<int> *e) {
	return (void)(e[u].push_back(v)), 1;
}

void tarjan(int u) {
	low[u] = dfn[u] = ++t;
	s.push(u), ins[u] = true;
	for (auto v : e[u]) {
		if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if (ins[v]) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		int p;
		cnt++;
		do {
			p = s.top(), s.pop();
			ins[p] = false, fa[p] = cnt;
			new_w[cnt] += w[p], new_v[cnt] += v[p];
		} while (p != u);
	}
	return;
}

void dfs(int u) {
	for (int i = new_w[u]; i <= m; i++) dp[u][i] = new_v[u];
	for (auto v : new_[u]) {
		dfs(v);
		for (int i = m - new_w[u]; i >= 0; i--) 
			for (int j = 0; j <= i; j++) 
				dp[u][i + new_w[u]] = max(dp[u][i + new_w[u]], dp[v][j] + dp[u][i + new_w[u] - j]);
	}
	return;
}

void solve() {
	for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; i++) if (fa[i] != fa[d[i]]) add(fa[d[i]], fa[i], new_), in[fa[i]]++;
	for (int i = 1; i <= cnt; i++) if (!in[i]) add(0, i, new_);
	dfs(0);
	cout << dp[0][m] << endl;
	return;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> w[i];
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (int i = 1; i <= n; i++) cin >> d[i], (d[i] != 0 ? add(d[i], i, e) : 1);
	solve();
	return 0;
}