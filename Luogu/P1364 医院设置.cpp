#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

int n, a[105];
bool link[105][105];
int ans = 0x3f3f3f3f;
vector<int> e[105];
bool used[105];

int dfs(int u, int cnt = 0) {
	int res = cnt * a[u];
	for (auto i : e[u]) {
		if (!used[i]) used[i] = true, res += dfs(i, cnt + 1);
	}
	return res;
}

void solve() {
	for (int i = 1; i <= n; i++) {
		memset(used, 0, sizeof used);
		used[i] = true;
		ans = min(dfs(i), ans);
	}
	cout << ans << endl;
	return;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int w, u, v;
		cin >> w >> u >> v;
		a[i] = w;
		if (u) e[i].push_back(u), e[u].push_back(i);
		if (v) e[i].push_back(v), e[v].push_back(i);
	}
	solve();
	return 0;
}