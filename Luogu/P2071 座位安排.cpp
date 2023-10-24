#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 2e3 + 50;
int n;
vector<int> e[2 * N];
bool used[2 * N];
int ans, match[2 * N];

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
	for (int i = 1; i <= 2 * n; i++) {
		fill(used + 1, used + 2 * n + 1, false);
		if (dfs(i)) ans++;
	}
	cout << ans << endl;
	return;
}

int main() {
	cin >> n;
	for (int i = 1, u, v; i <= 2 * n; i++) 
		cin >> u >> v, add(i, u), add(i, v), add(i, u + n), add(i, v + n);
	solve();
	return 0;
}