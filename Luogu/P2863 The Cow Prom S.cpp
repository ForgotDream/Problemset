#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

const int N = 1e4 + 50;
int n, m, u, v;
vector<int> e[N];
int dfn[N], low[N], t, cnt;
stack<int> s;
bool ins[N];
int fa[N], num[N];
int ans;

void tarjan(int u) {
	s.push(u), ins[u] = true;
	dfn[u] = low[u] = ++t;
	for (auto v : e[u]) {
		if (!dfn[v]) tarjan(v), dfn[u] = min(dfn[u], dfn[v]);
		else if (ins[v]) dfn[u] = min(dfn[u], low[v]);
	}
	if (dfn[u] == low[u]) {
		cnt++;
		int p;
		do {
			p = s.top(), s.pop();
			fa[p] = cnt, num[cnt]++, ins[p] = false;
		} while (p != u);
	}
	return;
}

void solve() {
	for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= cnt; i++) ans += (num[i] > 1);
	return (void)(cout << ans << endl);
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) cin >> u >> v, e[u].push_back(v);
	solve();
	return 0;
}