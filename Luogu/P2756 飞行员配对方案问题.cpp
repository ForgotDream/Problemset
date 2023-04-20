#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1e3 + 50;
int n, m, c;
vector<int> e[N];
bool used[N];
int ans, match[N];

void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

bool dfs(int u) {
	for (auto v : e[u]) {
		if (!used[v]) {
			used[v] = true;
			if (!match[v] || dfs(match[v])) return match[v] = u, true;
		}
	}
	return false;
}

void solve() {
	for (int i = 1; i <= m; i++) {
		fill(used + 1, used + n + m + 1, false);
		if (dfs(i)) ans++;
	}
	cout << ans << endl;
	for (int i = m + 1; i <= n + m; i++)
		if (match[i]) cout << match[i] << ' ' << i << endl;
	return;
}

int main() {
	cin >> m >> n;
	n -= m;
	for (int i = 1, u, v; ; i++) {
		cin >> u >> v;
		if (u == -1) break;
		add(u, v);
	}
	solve();
	return 0;
}