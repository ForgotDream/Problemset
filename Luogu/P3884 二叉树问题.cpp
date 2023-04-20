#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int n;
vector<int> e[105];
int x, y;
int depth[105], bread[105], fa[105];
bool vis[105];
int ans;

void get_depth(int from, int u = 1, int step = 1) {
	vis[u] = true, depth[u] = step, fa[u] = from;
	for (auto v : e[u]) {
		if (vis[v]) continue;
		get_depth(u, v, step + 1);
	}
	return;
}

void get_breadth() {
	queue<int> q;
	q.push(1);
	vis[1] = true;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for (auto v : e[u]) {
			if (vis[v]) continue;
			vis[v] = true, bread[depth[v]]++;
			q.push(v);
		}
	}
	return;
}

int get_lca(int x, int y) {
	if (depth[y] > depth[x]) swap(y, x);
	while (depth[y] < depth[x]) x = fa[x], ans++;
	if (x == y) {
		return x;
	}
	// cout << x << ' ' << y << endl;
	while (x != y) x = fa[x], y = fa[y], ans += 2;
	// cout << x << ' ' << y << endl;
	return x;
}

void solve() {
	get_depth(1);
	for (int i = 1; i <= n; i++) ans = max(ans, depth[i]);
	cout << ans << endl;

	memset(vis, 0, sizeof vis);
	int max_dep = ans;
	ans = 0;

	get_breadth();
	for (int i = 1; i <= max_dep; i++) ans = max(ans, bread[i]);
	cout << ans << endl;

	ans = 0;
	int ans1 = 0, ans2 = 0;

	int f = get_lca(x, y);
	while (x != f) x = fa[x], ans1 += 2;
	while (y != f) y = fa[y], ans2++;
	cout << ans1 + ans2 << endl;
	return;
}

int main() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		e[u].push_back(v), e[v].push_back(u);
	}
	cin >> x >> y;
	solve();
	return 0;
}