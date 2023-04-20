#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1e3 + 50, M = 550;
int n, m;
vector<int> e[N];
int dfn[N], low[N], t;
bool cut[N];
int cnt, belong[N], num, root;
long long ans, res, cut_num;

void init() {
	for (int i = 1; i <= n; i++) e[i].clear();
	fill(dfn + 1, dfn + n + 1, 0), fill(low + 1, low + n + 1, 0);
	fill(belong + 1, belong + n + 1, 0), fill(cut + 1, cut + n + 1, 0);
	n = 0, ans = 1, cnt = 0, res = 0, t = 0;
	return;
}

void dfs(int u) {
	belong[u] = cnt, num++;
	if (cut[u]) return;
	for (auto v : e[u]) {
		if (cut[v] && belong[v] != cnt) belong[v] = cnt, cut_num++;
		if (!belong[v]) dfs(v);
	}
	return;
}

void tarjan(int u, int fa) {
	dfn[u] = low[u] = ++t;
	int child = 0;
	for (auto v : e[u]) {
		if (v == fa) continue;
		child++;
		if (!dfn[v]) {
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if (u == root && child > 1) cut[u] = true;
			else if (u != root && low[v] >= dfn[u]) cut[u] = true;
		} else low[u] = min(low[u], dfn[v]);
	}
	return;
}

void solve() {
	root = 1, tarjan(1, 0);
	for (int i = 1; i <= n; i++) if (!belong[i] && !cut[i]) {
			++cnt, cut_num = 0, num = 0, dfs(i);
			// cout << cut_num << endl;
			if (cut_num == 0) res += 2, ans *= (long long)(num - 1) * num / 2;
			else if (cut_num == 1) res += 1, ans *= num;
		}
	return;
}

int main() {
	for (int kase = 1; ; kase++) {
		init();
		cin >> m;
		if (!m) break;
		for (int i = 1, u, v; i <= m; i++) {
			cin >> u >> v;
			e[u].push_back(v), e[v].push_back(u), n = max(n, u), n = max(n, v);
		}
		solve();
		cout << "Case " << kase << ": " << res << ' ' << ans << endl;
	}
	return 0;
}