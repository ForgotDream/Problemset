#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int N = 1e6 + 50;
int n, m;
vector<int> e[2 * N];
int dfn[2 * N], low[2 * N], t;
bool ins[2 * N];
int fa[2 * N], cnt;
stack<int> s;

void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

void tarjan(int u) {
	dfn[u] = low[u] = ++t;
	s.push(u), ins[u] = true;
	for (auto v : e[u]) {
		if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if (ins[v]) low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		int p;
		++cnt;
		do {
			p = s.top(), s.pop();
			ins[p] = false;
			fa[p] = cnt;
		} while (p != u);
	}
	return;
}

void solve() {
	for (int i = 1; i <= 2 * n; i++) if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; i++) if (fa[i] == fa[i + n]) return (void)(cout << "IMPOSSIBLE" << endl);
	cout << "POSSIBLE" << endl;
	for (int i = 1; i <= n; i++) cout << (fa[i] > fa[i + n]) << ' ';
	cout << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1, x, xval, y, yval; i <= m; i++) {
		cin >> x >> xval >> y >> yval;
		add(x + n * (xval ^ 1), y + n * yval);
		add(y + n * (yval ^ 1), x + n * xval);
	}
	solve();
	return 0;
}