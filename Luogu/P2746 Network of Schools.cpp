#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

const int N = 105;
int n, ans1, ans2;
int u, v;
vector<int> e[N];
stack<int> s;
int dfn[N], low[N], cnt, t, fa[N], in[N], num[N], out[N];
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
		for (auto v : e[u]) if (fa[v] != fa[u]) in[fa[v]]++, out[fa[u]]++;
	for (int i = 1; i <= cnt; i++) if (!in[i]) ans1++;
	for (int i = 1; i <= cnt; i++) if (!out[i]) ans2++;
	cout << ans1 << endl << (cnt > 1 ? max(ans1, ans2) : 0) << endl;
	return;	
}

int main() {
	cin >> n;
	for (u = 1; u <= n; u++) 
		while (cin >> v && v != 0) e[u].push_back(v);
	solve();
	return 0;
}