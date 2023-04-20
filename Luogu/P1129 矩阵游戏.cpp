#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int N = 250;
int n, t;
vector<int> e[2 * N];
bool used[2 * N];
int ans, match[2 * N];

void init() {
	ans = 0;
	fill(used + 1, used + 2 * n + 1, false);
	fill(match + 1, match + 2 * n + 1, 0);
	for (int i = 1; i <= 2 * n; i++) e[i].clear();
	return;
}

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
	for (int i = 1; i <= n; i++) {
		fill(used + 1, used + 2 * n + 1, false);
		if (dfs(i)) ans++;
	}
	// cout << ans << endl;
	if (ans >= n) cout << "Yes" << endl;
	else cout << "No" << endl;
	return;
}

int main() {
	cin >> t;
	while (t--) {
		init();
		cin >> n;
		for (int i = 1; i <= n; i++)
			for (int j = 1, tmp; j <= n; j++) {
				cin >> tmp;
				if (tmp) add(i, j + n);
			}
		solve();
	}
	return 0;
}