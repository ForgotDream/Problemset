#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>

using namespace std;
using Edge = pair<int, int>;

const int N = 3050, INF = 0x3f3f3f3f;
int n, p, r;
int u, v;
int a[N];
vector<int> e[N], new_[N];
vector<Edge> edge;
stack<int> s;
int dfn[N], low[N], cnt, t, fa[N], num[N];
bool ins[N];
queue<int> q;
int in[N], ans;

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
		num[++cnt] = INF;
		do {
			p = s.top(), s.pop();
			ins[p] = false;
			fa[p] = cnt, num[cnt] = min(a[p], num[cnt]);
		} while (p != u);
	}
	return;
}

void solve() {
	for (int i = 1; i <= n; i++) if (!dfn[i] && a[i] != INF) tarjan(i);
	for (int i = 1; i <= n; i++) if (!dfn[i]) return (void)(cout << "NO" << endl << i << endl);
	for (auto i : edge) {
		int u = i.first, v = i.second;
		if (fa[u] != fa[v]) add(fa[u], fa[v], new_), in[fa[v]]++;
	}
	for (int i = 1; i <= cnt; i++) if (!in[i]) ans += num[i];
	return (void)(cout << "YES" << endl << ans << endl);
}

int main() {
	cin >> n >> p;
	memset(a, 0x3f, sizeof a);
	for (int i = 1; i <= p; i++) {
		int no, w;
		cin >> no >> w;
		a[no] = w;
	}
	cin >> r;
	for (int i = 1; i <= r; i++) cin >> u >> v, add(u, v, e), edge.emplace_back(u, v);
	solve();
	return 0;
}