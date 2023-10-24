#include <cstdio>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;
using Edge = pair<int, int>;

const int N = 1e5 + 50, M = 1e6 + 50;
int n, m, x;
int u, v;
vector<int> e[N], new_[N];
vector<Edge> ee;
stack<int> s;
queue<int> q;
int dfn[N], low[N], num[N];
bool ins[N];
int fa[N], t, cnt;
int in[N], dis[N], f[N];
int ans1, ans2;

void add(int u, int v, vector<int> *g) {
	return (void)g[u].push_back(v);
}

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

void uni() {
	/*
	cout << cnt << endl;
	for (int i = 1; i <= n; i++) cout << fa[i] << ' ';
	cout << endl;
	for (int i = 1; i <= cnt; i++) {
		cout << i << "(" << num[i] << "): ";
		for (auto j : new_[i]) cout << j << ' ';
		cout << endl;
	}
	*/
	for (int i = 1; i <= cnt; i++) {
		sort(new_[i].begin(), new_[i].end());
		new_[i].erase(unique(new_[i].begin(), new_[i].end()), new_[i].end());
	}
	/*
	for (int i = 1; i <= cnt; i++) {
		cout << i << ": ";
		for (auto j : new_[i]) cout << j << ' ';
		cout << endl;
	}
	*/
	return;
}

void topo() {
	for (int i = 1; i <= cnt; i++) if (!in[i]) q.push(i), dis[i] = num[i], f[i] = 1;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (auto v : new_[u]) {
			// dis[v] = max(dis[v], dis[u] + num[v]);
			if (dis[v] == dis[u] + num[v]) {
				f[v] = (f[v] + f[u]) % x;
			} else if (dis[v] < dis[u] + num[v]) {
				dis[v] = dis[u] + num[v];
				f[v] = f[u];
			}
			if (!--in[v]) q.push(v);
		}
	}
	return;
}

void solve() {
	for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
	for (auto i : ee) {
		int from = i.first, to = i.second;
		if (fa[from] != fa[to]) add(fa[from], fa[to], new_);
	}
	uni();
	for (int i = 1; i <= cnt; i++)
		for (auto j : new_[i]) in[j]++;
	topo();
	for (int i = 1; i <= cnt; i++) {
		if (dis[i] > dis[ans1]) ans1 = i, ans2 = f[i];
		else if (dis[i] == dis[ans1]) ans2 = (ans2 + f[i]) % x;
	}
	// for (int i = 1; i <= cnt; i++) cout << f[i] << endl;
	cout << dis[ans1] << endl << ans2 << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m >> x;
	for (int i = 1; i <= m; i++) cin >> u >> v, add(u, v, e), ee.push_back(make_pair(u, v));
	solve();
	return 0;
}