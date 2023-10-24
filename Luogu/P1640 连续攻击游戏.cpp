#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int N = 1e6 + 50, M = 1e4;
int n, t;
vector<int> e[2 * N];
int used[N];
int ans, match[N];
int maxx;

void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

void update(int u, int v) {
	maxx = max(maxx, u);
	maxx = max(maxx, v);
	return;
}

bool dfs(int u) {
	for (auto v : e[u]) {
		if (used[v] != t) {
			used[v] = t;
			if (!match[v] || dfs(match[v])) return match[v] = u, true;
		}
	}
	return false;
}

void solve() {
	for (int i = 1; i <= maxx; i++) {
		++t;
		// fill(used + 1, used + n + 1, false);
		if (dfs(i)) ans++;
		else break;
	}
	cout << ans << endl;
	return;
}

int main() {
	cin >> n;
	for (int i = 1, u, v; i <= n; i++) 
		cin >> u >> v, add(u, i), add(v, i), update(u, v);
	solve();
	return 0;
}