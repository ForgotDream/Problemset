#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

vector<int> e[100005];
int n, t, k, ans;
int siz[100005];

void solve(int u, int fa) {
	siz[u] = 1;
	for (auto v : e[u]) {
		if (v == fa) continue;
		solve(v, u), siz[u] += siz[v];
	}
	if (siz[u] == k) ans++, siz[u] -= k;
	return;
}

int main() {
	cin >> t;
	while (t--) {
		memset(siz, 0, sizeof siz);
		// e.clear();
		for (int i = 1; i <= n; i++) e[i].clear();
		ans = 0;
		cin >> n >> k;
		for (int i = 1; i < n; i++) {
			int u, v;
			cin >> u >> v;
			e[u].push_back(v);
			e[v].push_back(u);
		}
		if (n % k) {
			cout << "NO" << endl;
			continue;
		}
		solve(1, 0);
		if (ans == n / k) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}