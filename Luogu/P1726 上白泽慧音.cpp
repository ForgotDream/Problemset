#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

const int N = 1e4 + 50;
int n, m, cnt;
int dfn[N], low[N];
int u, v, type;
vector<int> e[N];
stack<int> s;
bool ins[N];
int fa[N], num[N];
int t, ans = 0, no;

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

void solve() {
	for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= cnt; i++) 
		if (ans < num[i]) ans = num[i], no = i;
	cout << ans << endl;
	for (int i = 1; i <= n; i++) 
		if (fa[i] == no) cout << i << ' ';
	return;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {cin >> u >> v >> type, e[u].push_back(v);
		if (type == 2) e[v].push_back(u);
	}
	solve();
	return 0;
}