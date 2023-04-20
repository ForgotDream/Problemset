#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;
using ll = long long;

const int N = 2e5 + 50, INF = 0x3f3f3f3f, MOD = 1e9 + 7;
int n, m;
int a[N];
int u, v, w;
vector<int> e[N];
stack<int> s;
int dfn[N], low[N], cnt, t, fa[N], num[N], ini[N];
bool ins[N];
ll ans1, ans2 = 1;

void add(int u, int v, vector<int> *e) {
	return (void)(e[u].push_back(v));
}

void tarjan(int u) {
	dfn[u] = low[u] = ++t;
	s.push(u), ins[u] = true;
	for (auto v : e[u]) 
		if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if (ins[v]) low[u] = min(low[u], dfn[v]);
	if (dfn[u] == low[u]) {
		num[++cnt] = INF;
		int p;
		do {
			p = s.top(), s.pop();
			fa[p] = cnt, ins[p] = false;
			if (num[cnt] > a[p]) num[cnt] = a[p], ini[cnt] = 1;
			else if (num[cnt] == a[p]) ini[cnt]++;
		} while (p != u);
	}
	return;
}

void solve() {
	for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= cnt; i++) 
		ans1 += num[i], ans2 = (ans2 * ini[i]) % MOD;
	cout << ans1 << ' ' << ans2 << endl;
	return;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	cin >> m;
	for (int i = 1; i <= m; i++) cin >> u >> v, add(u, v, e);
	solve();
	return 0;
}