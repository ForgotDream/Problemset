#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Edge = pair<int, int>;

const int N = 1e6 + 50, INF = 0x3f3f3f3f;
vector<int> e[N];
int n, w[N], siz[N], sum, rt;
int ans[3], cnt;

inline void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

void dfs(int u, int from) {
	siz[u] = w[u];
	for (int v : e[u]) {
		if (v == from) continue;
		dfs(v, u), siz[u] += siz[v];
	}
	if (siz[u] == sum) ans[++cnt] = u, siz[u] = 0;
	return;
}

void solve() {
	if (sum % 3 || sum == 0) return (void)(cout << -1 << endl);
	sum /= 3, dfs(rt, 0);
	if (ans[1] && ans[2]) cout << ans[1] << ' ' << ans[2] << endl;
	else cout << -1 << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for (int i = 1, f; i <= n; i++) {
		cin >> f >> w[i], sum += w[i]; 
		if (f) add(f, i), add(i, f);
		else rt = i;
	}
	solve();
	return 0;
}