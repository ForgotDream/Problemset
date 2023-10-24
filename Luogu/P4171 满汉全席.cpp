#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

const int N = 105;
int T;
int n, m;
vector<int> e[2 * N];
stack<int> st;
int dfn[2 * N], low[2 * N], fa[2 * N], cnt, t;
bool ins[2 * N];

void init() {
	fill(dfn + 1, dfn + 2 * n + 1, 0), fill(low + 1, low + 2 * n + 1, 0);
	fill(fa + 1, fa + 2 * n + 1, 0);
	t = cnt = 0;
	for (int i = 1; i <= 2 * n; i++) e[i].clear();
	return;
}

void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

void tarjan(int u) {
	dfn[u] = low[u] = ++t;
	st.push(u), ins[u] = true;
	for (auto v : e[u]) {
		if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if (ins[v]) low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		int p;
		++cnt;
		do {
			p = st.top(), st.pop();
			ins[p] = false;
			fa[p] = cnt;
		} while (p != u);
	}
	return;
}

void solve() {
	for (int i = 1; i <= 2 * n; i++) if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; i++) if (fa[i] == fa[i + n]) return (void)(cout << "BAD" << endl);
	cout << "GOOD" << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> T;
	while (T--) {
		init();
		cin >> n >> m;
		for (int i = 1; i <= m; i++) {
			char c1, c2;
			int no1, no2;
			cin >> c1 >> no1 >> c2 >> no2;
			if (c1 == 'm' && c2 == 'm') add(no1, no2 + n), add(no2, no1 + n);
			else if (c1 == 'm' && c2 == 'h') add(no1, no2), add(no2 + n, no1 + n);
			else if (c1 == 'h' && c2 == 'h') add(no1 + n, no2), add(no2 + n, no1);
			else if (c1 == 'h' && c2 == 'm') add(no1 + n, no2 + n), add(no2, no1);
		}
		// for (int i = 1; i <= n; i++) add(), add();
		solve();
	}
	return 0;
}