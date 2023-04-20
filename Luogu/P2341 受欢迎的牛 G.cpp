#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

const int N = 1e4 + 50;
int n, m, cnt;
int dfn[N], low[N];
int u, v;
vector<int> e[N];
stack<int> s;
bool ins[N];
int fa[N], num[N], out[N], no;
int t;

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
	for (int u = 1; u <= n; u++) 
		for (auto v : e[u]) if (fa[v] != fa[u]) out[fa[u]]++;
	for (int i = 1; i <= cnt; i++) 
		if (!out[i]) {
			if (no) {
				cout << 0 << endl;
				return;
			} else no = i;
		}
	cout << num[no] << endl;
	return;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) cin >> u >> v, e[u].push_back(v);
	solve();
	return 0;
}